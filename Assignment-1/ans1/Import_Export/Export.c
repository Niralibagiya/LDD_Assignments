#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include "Export.h"

static int __init vdg_init(void)
{
    num = 100;
    printk(KERN_INFO "This is the module with multiple exported symbols...\n");
    return 0;
}
static void __exit vdg_exit(void)
{
    printk(KERN_INFO "Exiting From Module With Multiple Exported Symbols...\n");
}

void exportedFuction(void)
{
    printk(KERN_INFO "I am an Exported Function...\n");
}

module_init(vdg_init);
module_exit(vdg_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("nirali soni <nirsoni@gmail.com>");
MODULE_DESCRIPTION("VDG: Module with Multiple Exported Symbols");

EXPORT_SYMBOL(num);
EXPORT_SYMBOL(exportedFuction);
