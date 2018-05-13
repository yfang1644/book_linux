/* jit_current.c
 */

#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

static int opened = 0;   /* 每次打开只读一次 */
int currenttime_open(struct inode *inode, struct file *filp)
{
    opened = 1;
    return 0;
}

ssize_t currenttime_read(struct file *file,
                         char *buffer,
                         size_t count,
                         loff_t *f_pos)
{
    int len;
    struct timeval tv1;
    struct timespec tv2;
    unsigned long j1;
    
    if(opened == 0)
        return 0;
    opened = 0;
    j1 = jiffies ;
    do_gettimeofday(&tv1);
    tv2 = current_kernel_time();

    /* print */
    len = sprintf(buffer, "0x%08lx %10i.%06i\n"
                  "%22i.%09i\n",
                  j1 ,
                  (int)tv1.tv_sec, (int)tv1.tv_usec,
                  (int)tv2.tv_sec, (int)tv2. tv_nsec);

    return len;
}

struct file_operations fops = {
    owner: THIS_MODULE,
    open: currenttime_open,
    read: currenttime_read,
};

int init_module(void)
{
    proc_create("currenttime", 0666, NULL, &fops);
    return 0;
}

void cleanup_module(void)
{
    remove_proc_entry("currenttime", NULL);
}
