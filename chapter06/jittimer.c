/* jittimer.c
 */

#include <linux/kernel.h>
#include <linux/module.h>
  
#include <linux/timer.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

#define LIMIT	(PAGE_SIZE-128)

static DECLARE_WAIT_QUEUE_HEAD (jiq_wait);

static struct clientdata {
    struct seq_file *m;
    unsigned long jiffies;
    int wait_cond;
} jiq_data;

/* 打印；任务重新调度时返回非零 */
static int jiq_print(void *ptr)
{
    struct clientdata *data = ptr;
    struct seq_file *m = data->m;
    unsigned long j = jiffies;

    if (m->count > LIMIT) {
        data->wait_cond = 1;
        wake_up_interruptible(&jiq_wait);
        return 0;
    }

    if (m->count == 0)
        seq_puts(m,"    time  delta preempt   pid cpu command\n");

    seq_printf(m, "%9li  %4li     %3i %5i %3i %s\n",
               j, j - data->jiffies,
               preempt_count(), current->pid, smp_processor_id(),
               current->comm);

    data->jiffies = j;
    return 1;
}

static void jiq_timedout(unsigned long ptr)
{
    struct clientdata *data = (void*)ptr;
    jiq_print((void *)data);            /* print a line */

    data->wait_cond = 1;               /* 睡眠结束的条件 */
    wake_up_interruptible(&jiq_wait);  /* 唤醒 */
}

static int jiq_read_run_timer(struct seq_file *m, void *v)
{
    struct timer_list jiq_timer;

    jiq_data.m = m;
    jiq_data.jiffies = jiffies;
    jiq_data.wait_cond = 0;

    init_timer(&jiq_timer);         /* 初始化定时器结构 */
    jiq_timer.function = jiq_timedout;
    jiq_timer.data = (unsigned long)&jiq_data;
    jiq_timer.expires = jiffies + HZ;   /* 准备睡眠 1 秒 */

    jiq_print(&jiq_data);          /* 打印数据，睡眠 */
    add_timer(&jiq_timer);
    wait_event_interruptible(jiq_wait, jiq_data.wait_cond);
    del_timer_sync(&jiq_timer);  /* 删除定时器 */

    return 0;
}

static int jiq_read_run_timer_proc_open(struct inode *inode,
                                        struct file *file)
{
    return single_open(file, jiq_read_run_timer, NULL);
}

struct file_operations jiq_proc_fops = {
    open: jiq_read_run_timer_proc_open,
    read: seq_read,
};

int init_module(void)
{
    proc_create("jitimer", 0, NULL, &jiq_proc_fops);
    return 0; /* succeed */
}

void cleanup_module(void)
{
    remove_proc_entry("jitimer", NULL);
}
