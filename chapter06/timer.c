/* timer.c
 * Create an input/output character device
 */

#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>           /* file_operations 结构 */      
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/ioport.h>       /* inb()、outb() 函数 */
#include <linux/uaccess.h> 	    /* 内核/用户空间存储器复制 */

#include "timer.h"

int timer_open(struct inode *inode, 
               struct file *filp)
{
    dev_t dev = inode->i_rdev;
    struct dtimer *i8254;

    printk("%X\n", dev);

    filp->f_pos = 0;
    if (filp->private_data == NULL) {
        filp->private_data = kmalloc(sizeof(struct dtimer), GFP_KERNEL);
        printk("MALLOC\n");
    }
    i8254 = (struct dtimer *)filp->private_data;
    i8254->port = MINOR(dev) + 0x40;   /* 8254端口基地址 0x40 */

    return 0;
}

static int timer_release(struct inode *inode, 
                          struct file *filp)
{
    struct dtimer *i8254 = (struct dtimer *)filp->private_data;
    printk("%X", i8254->port);
    if (filp->private_data != NULL) {
        kfree(filp->private_data);
        filp->private_data = NULL;
    }
	return 0;
}

/* This function is called when somebody tries to 
 * write into our device file. */ 
static ssize_t timer_write(struct file *filp,
                           const char *buf,
                           size_t count,
                           loff_t *offset)
{
	char val[2];
    struct dtimer *i8254;
    int port, len;
    int i;

    len = count;
    if (count > 2) {
        count = 2;
    }
	copy_from_user(val, &buf[len-count], count);

    i8254 = (struct dtimer *)filp->private_data;
    port = i8254->port;

    for(i = 0; i < count; i++)
        outb(val[i], port);	

	return count;
}

/* This function is called when our device file is read */
ssize_t timer_read(struct file *filp,
                   char *buf,
                   size_t count,
                   loff_t *offset)
{
    struct dtimer *i8254 = (struct dtimer *)filp->private_data;
    int port = i8254->port;
    int retval;

    if (filp->f_pos >= 1024) { /* all 1024 bytes are read */
        filp->f_pos = 0;
        return 0;                     
    }
    if (filp->f_pos == 0) {    /* read 1024 bytes each time */
        printk("%x\n", port);
        outb(0x01, 0x61);
        insb(port, i8254->buf, 1024);
    }
    if(filp->f_pos + count > 1024) {
        count = 1024 - filp->f_pos;
    }
    retval = copy_to_user(buf, i8254->buf + filp->f_pos, count);
    filp->f_pos += count - retval;
	return count - retval;
}

loff_t timer_llseek(struct file *filp,
                    loff_t off,
                    int whence)
{
    loff_t newpos;
    switch(whence) {
    case SEEK_SET:
        newpos = off;
        break;
    case SEEK_CUR:
        newpos = filp->f_pos + off;
        break;
    case SEEK_END:
        newpos = 1024 + off;
        break;
    default:       /* can't happen */
        return -EINVAL;
    }

    if (newpos < 0)
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}

long timer_ioctl(struct file *filp,
                 unsigned int cmd,
                 unsigned long arg)
{
    int err = 0, tmp;
    int ret = 0;
    struct dtimer *i8254;
    int port, portnum;
    int cntbit;
    unsigned char oldstatus, status;

    if (_IOC_TYPE(cmd) != IOCTL_MAGIC)
        return -ENOTTY;
    if (_IOC_NR(cmd) > TIMER_IOC_MAXNR)
        return -ENOTTY;

    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
    if (err)
        return -EFAULT;

    i8254 = (struct dtimer *)filp->private_data;
    port = i8254->port;
    portnum = (port & 3) << 6;
    cntbit = 2 << (port & 3);
    outb(0b11100000|cntbit, 0x43);      /* 发控制寄存器回读命令 */
    oldstatus = inb(port);              /* 读控制寄存器 */

    switch(cmd) {
    case TIMER_IOCRESET:     /* 复位 */
    case TIMER_SPEAKEROFF:   /* 关闭扬声器开关 */
        outb(0x0, 0x61);
        ret = 0;
        break;
    case TIMER_SPEAKERON:    /* 打开扬声器开关 */
        outb(0x3, 0x61);
        ret = 0;
        break;

    case TIMER_IOCSMODE:     /* Set模式: 传入参数指针 */
        ret = get_user(status, (int *)arg);
        status = (status << 1) | portnum;
        oldstatus &= (TIMER_HIGH|TIMER_LOW);
        status |= oldstatus;
        outb(status, port);
        break;
    case TIMER_IOCTMODE:     /* Tell模式: 传入参数值 */
        status = (arg << 1) | portnum;
        oldstatus &= (TIMER_HIGH|TIMER_LOW);
        status |= oldstatus;
        outb(status, port);
        ret = 0;
        break;
    case TIMER_IOCGMODE: /* Get模式: 返回参数指针 */
        oldstatus &= 0b00001110;
        oldstatus >>= 1;
        ret = put_user(oldstatus, (char *)arg);
        break;
    case TIMER_IOCQMODE:    /* Query模式: 返回参数值 */
        oldstatus &= 0b00001110;
        ret = oldstatus >> 1;
        break;
    case TIMER_IOCXMODE:    /* eXchange模式: 传入指针，返回指针 */
        ret = get_user(status, (int *)arg);
        if (ret == 0) {
            tmp = (oldstatus & 0b00001110) >> 1;
            ret = put_user(tmp, (int *)arg);
            oldstatus &= (TIMER_HIGH|TIMER_LOW);
            status = (status << 1) | portnum;
            status |= oldstatus;
            outb(status, port);
        }
        break;
    case TIMER_IOCHMODE: /* sHift模式: 传入参数值，返回参数值 */
        status = (arg << 1) | portnum;
        status |= (oldstatus & (TIMER_HIGH|TIMER_LOW));
        outb(status, port);
        oldstatus &= 0b00001110;
        ret = oldstatus >> 1;
        break;

    case TIMER_IOCSBYTE:
        ret = get_user(status, (int *)arg);
        status |= portnum;
        oldstatus &= 0b00001110;
        status |= oldstatus;
        outb(status, port);
        break;
    case TIMER_IOCTBYTE:
        status = arg | portnum;
        oldstatus &= 0b0001110;
        status |= oldstatus;
        outb(status, port);
        ret = 0;
        break;
    case TIMER_IOCGBYTE:
        oldstatus &= (TIMER_HIGH|TIMER_LOW);
        ret = put_user(oldstatus, (char *)arg);
        break;
    case TIMER_IOCQBYTE:
        ret = oldstatus & (TIMER_HIGH|TIMER_LOW);
        break;
    case TIMER_IOCXBYTE:
        ret = get_user(status, (int *)arg);
        if (ret == 0) {
            tmp = oldstatus & (TIMER_HIGH|TIMER_LOW);
            ret = put_user(tmp, (int *)arg);
            oldstatus &= 0b00001110;
            status |= portnum;
            status |= oldstatus;
            outb(status, port);
        }
        break;
    case TIMER_IOCHBYTE:
        status = arg | portnum;
        status |= (oldstatus & 0b00001110);
        outb(status, port);
        ret = oldstatus & (TIMER_HIGH|TIMER_LOW);
        break;
    default:
        return -ENOTTY;
    }
    return ret;
}

struct file_operations fops = {
    owner:	THIS_MODULE,
    open:	timer_open,
    llseek: timer_llseek,
    release:	timer_release,
	unlocked_ioctl:	timer_ioctl,
    read:	timer_read,
    write:	timer_write,
};

static int major = 123, minor = 0;

/* 模块初始化，注册设备 */
int init_module(void)
{
    int retval;

    retval = register_chrdev(major, "timer", &fops);
    return retval;
}

/* 注销设备，清除模块 */
void cleanup_module(void)
{
    unregister_chrdev(major, "timer");
}

MODULE_LICENSE("GPL");
