/* jiffies.c
 */

#include <linux/module.h>
#include <linux/sched.h>
    
int init_module()
{
    long now = jiffies;

    printk("start at %ld\n", now);
    while(jiffies < now + 3600*HZ)
        ;
              
    printk("stop at %ld\n", jiffies);

    return -1;
}
