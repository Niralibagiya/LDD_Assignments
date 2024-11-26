#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/kobject.h>

static int __init list_modules_init(void) 
{
    struct module *mod;

    printk(KERN_INFO "all current loaded modules:\n");

   
    list_for_each_entry(mod, THIS_MODULE->list.prev, list) {
        printk(KERN_INFO "Module: %s, Size: %u, State: %s\n", mod->name,mod->core_size,mod->state == MODULE_STATE_LIVE ?"LIVE": mod->state == MODULE_STATE_COMING ? "COMING" : mod->state == MODULE_STATE_GOING ? "GOING" : "UNKNOWN");
    }

    return 0;
}

static void __exit list_modules_exit(void) {
    printk(KERN_INFO "Unloading list_modules module.\n");
}

module_init(list_modules_init);
module_exit(list_modules_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Module to List All Loaded Modules");
MODULE_AUTHOR("Nirali_soni<nsoni07@gmail.com>");

