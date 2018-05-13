/* sleepy.c
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/wait.h>

#define DEVICE_NAME "sleepy"
#define MAJOR_NUM   234

static DECLARE_WAIT_QUEUE_HEAD (wq );
static int flag = 0;

ssize_t sleepy_read(struct file *filp,
                    char *buffer,
                    size_t length,
                    loff_t *offset)
{
    printk("Process %i (%s) is going to sleep.\n",
           current->pid, current->comm);
    wait_event_interruptible(wq, flag != 0);
    flag = 0;
    printk("Awoken %i (%s).\n", current->pid, current->comm );

    return 0;
}

ssize_t sleepy_write(struct file *filp,
                     const char *buffer,
                     size_t length,
                     loff_t *offset)
{
    printk("Process %i (%s) is awakening the readers ...\n",
           current->pid, current->comm);
    flag = 1;
    wake_up_interruptible(&wq);

    return length;
}

struct file_operations fops = {
    read: sleepy_read,
    write: sleepy_write
};

int init_module(void)
{
    int major;
    major = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
    if (major == 0) {
        printk("Device registed.\n");
        return 0;
    } else
        return -1;
}

void cleanup_module(void)
{
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}
