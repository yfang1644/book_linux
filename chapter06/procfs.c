/* procfs.c
 */

#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROCFS_NAME    "proctest"
#define PROCFS_MAX_SIZE 4096

static char procfs_buffer[4096];
int procfs_buffer_size = 4096; 
ssize_t procfile_read(struct file *file,
                      char *buffer,
                      size_t count,
                      loff_t *f_pos)
{
    int ret;

    printk(KERN_INFO "procfile_read (/proc/%s) called.\n", PROCFS_NAME);

    if (f_pos > 0) {    /* 数据读完 */
        ret  = 0;
    } else {            /* 填充缓冲区 */
        memcpy(buffer, procfs_buffer, procfs_buffer_size);
        ret = procfs_buffer_size;
    }
    return ret;
}

ssize_t procfile_write(struct file *file,
                       const char *buffer,
                       size_t count,
                       loff_t *f_pos)
{
    printk(KERN_INFO "procfile_write (/proc/%s) called.\n", PROCFS_NAME);
    /* 获得不超过缓冲区大小的size */
    procfs_buffer_size = count;

    if (procfs_buffer_size > PROCFS_MAX_SIZE)
        procfs_buffer_size = PROCFS_MAX_SIZE;
        
    if(copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
        return -EFAULT;
        
    return procfs_buffer_size;
}

struct file_operations fops = {
    owner:  THIS_MODULE,
    read:   procfile_read,
    write:  procfile_write
};

static struct proc_dir_entry *myprocfile;
int init_module()
{
    /* 创建 proc 文件 */

    myprocfile = proc_create(PROCFS_NAME, 0666, NULL, &fops);

    if (myprocfile == NULL) {   /* 创建失败 */
        remove_proc_entry(PROCFS_NAME, myprocfile);
        printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
                 PROCFS_NAME);
        return -ENOMEM;
    }
           
    printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
    return 0;   /*  everything is ok */
}

void cleanup_module()
{
    /* 删除 proc 文件 */
    remove_proc_entry(PROCFS_NAME, NULL);
}
