/* example.c
 */

# include <linux/module.h>
# include <linux/kernel.h>

int init_module(void)
{
    printk("<1> Module installed.\n");
    return 0;
}

void cleanup_module(void)
{
    printk("<1> Module removed.\n");
}
