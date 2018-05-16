/* gpio.c
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "gpio.h"

#ifdef DEBUG
#define PRINT   printk
#else
#define PRINT   
#endif

//volatile unsigned int *gpio;
//volatile unsigned int *ctrl;

int led_open (struct inode *inode, struct file *filp)
{ // fd = open(filename, OP)
    int minor_dev = MINOR(inode->i_rdev);
    int val;
    gpio_t *gpio;

    printk("minor = %d\n", minor_dev);
    filp->private_data = kmalloc(sizeof(gpio_t), GFP_KERNEL);
    gpio = (gpio_t *)filp->private_data;

    gpio->ctrl = ioremap(CONTRL, 128*1024);

    if(minor_dev == 1) {
        gpio->port= ioremap(GPIO1, 4096);
        gpio->ctrl[AD12]  = 0x37;       /* GPIO1[12] */
        gpio->ctrl[AD13]  = 0x37;       /* GPIO1[13] */
  //      val = 0xFFFFCFFF;
  //      gpio->port[OE] = val;
    } else if(minor_dev == 2) {
        gpio->port = ioremap(GPIO2, 4096);
    }

    return 0;
}

int led_close (struct inode *inode, struct file *filp)
{// close(fd);
    gpio_t *gpio;

    gpio = (gpio_t *)filp->private_data;
    iounmap(gpio->port);
    iounmap(gpio->ctrl);

    kfree(filp->private_data);
    return 0;
}

ssize_t led_read (struct file *filp,
                  char __user *buf,
                  size_t size,
                  loff_t *offset)
{  // n = read(fd, *buf, count);
    gpio_t *gpio = (gpio_t *)filp->private_data;
    int val, n;

    val = gpio->port[DATIN];
    n = copy_to_user(buf, &val, sizeof(val));

    return size;
}
ssize_t led_write (struct file *filp,
                   const char __user *buf,
                   size_t size,
                   loff_t *offset)
{ // n = write(fd, *buf, size);
    gpio_t *gpio = (gpio_t *)filp->private_data;
    int val, n;
    n = copy_from_user(&val, buf, size);
    if (size > 4)  size = 4;
//    printk("value  %x write to device\n", val);
    gpio->port[DATOUT] = val;

    return size;
}

long led_ioctl(struct file *filp,
               unsigned int cmd,
               unsigned long arg)
{
    //   ioctl(fd, LEDIOSET, &arg);
    gpio_t *gpio = (gpio_t *)filp->private_data;
    int val, n;

    switch(cmd) {
        case LEDIOSET:
            n = copy_from_user(&val, (unsigned int *)arg, 4);
            gpio->port[OE] = val;
            break;
        case LEDIOGET:
            val = gpio->port[OE];
            n = copy_to_user((unsigned int *)arg, &val, 4);
            break;
        default:
            break;
    }

    return 0;
}

struct file_operations fop={
    .open    = led_open,
    .release = led_close,
    .read    = led_read,
    .write   = led_write,
    .unlocked_ioctl = led_ioctl,
};

int init_module(void)
{
    int val;

    val = register_chrdev(223, "gpio LED", &fop);

    if (val == 0) {
        printk("Module installed.\n");
    } else {
        printk("Module register failed.\n");
    }
    return val;
}

void cleanup_module(void)
{
    unregister_chrdev(223, "gpio LED");
    printk("module removed from kernel.\n");
}
