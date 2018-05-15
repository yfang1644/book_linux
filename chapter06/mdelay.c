/* mdelay.c
 */

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
    
int init_module()
{
    int cnt;

    printk("start at %ld\n", jiffies);
    for(cnt = 0; cnt < 3600; cnt++)
        mdelay(1000);
              
    printk("stop at %ld\n", jiffies);

    return -1; 
}
