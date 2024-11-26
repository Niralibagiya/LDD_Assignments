#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int __init list_processes_init(void)
{
    struct task_struct *task;

    printk(KERN_INFO "Listing processes starting from the current process:\n");

    task = current;
    while (task != NULL) 
    {
        printk(KERN_INFO "Process: %s [PID: %d]\n", task->comm, task->pid);
        if (task->parent == task)
            break;
        task = task->parent;
    }

    return 0;
}

static void __exit list_processes_exit(void) 
{
    printk(KERN_INFO "Unloading list_processes module.\n");
}

module_init(list_processes_init);
module_exit(list_processes_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Module to List Processes Starting from Current Process");
MODULE_AUTHOR("Nirali soni<nsoni07@gmail.com>");

