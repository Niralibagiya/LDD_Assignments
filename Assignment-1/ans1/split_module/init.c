#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ASTROMEDICOM");
MODULE_DESCRIPTION("VDG:Two File Kernel Module");

static int vdg_init(void)
{
    printk(KERN_INFO "this is the module with two files..\n");
    return 0;
}

module_init(vdg_init);