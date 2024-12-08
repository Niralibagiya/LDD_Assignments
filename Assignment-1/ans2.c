#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/sched.h>

static dev_t first;
static struct cdev my_char_dev;
static struct class *my_device_class_ptr;
#define MAXLEN 4000
static char mybuffer[MAXLEN];

static int vdg_open(struct inode *inode_ptr,struct file *file_ptr)
{
    printk(KERN_INFO "VDG Drivers open() : PID of process using this device is %d\n",current->pid);
    return (0);
}

static int vdg_close(struct inode *inode_ptr,struct file *file_ptr)
{
    printk(KERN_INFO "VDG Drivers close()\n");
    return(0);
}

static ssize_t vdg_read(struct file *file_ptr,char __user *buffer,size_t length,loff_t *offset)
{
    int max_bytes;
    int bytes_to_read;
    int nbytes;
    max_bytes=MAXLEN- *offset;
    if(max_bytes>length)
     bytes_to_read=length;
     else
     bytes_to_read=max_bytes;
     if(bytes_to_read==0)
     {
        printk(KERN_INFO "VDG Drivers read():EOD (End of Device)\n");
        return(-ENOSPC);
     }
     nbytes=bytes_to_read-copy_to_user(buffer,mybuffer+*offset,bytes_to_read);
     *offset=*offset+nbytes;
     return(nbytes);
     }

static ssize_t vdg_write(struct file *file_ptr,const char __user *buffer,size_t length,loff_t *offset)
{
 int max_bytes;
 int bytes_to_write;
 int nbytes;
 max_bytes=MAXLEN- *offset;
 if(max_bytes>length)
 bytes_to_write=length;
 else
 bytes_to_write=max_bytes;
 if(bytes_to_write==0)
 {
    pr_info("VDG Drivers write():EOD (End of Device)\n");
    return(-ENOSPC);
 }  
 nbytes=bytes_to_write-copy_from_user(mybuffer+ *offset,buffer,bytes_to_write);
 *offset=*offset+nbytes;
 return(nbytes);
}

static loff_t vdg_lseek(struct file *file_ptr,loff_t offset,int origin)
{
    loff_t new_pos=0;
    switch(origin)
    {
    case 0:
        new_pos=offset;
        break;
    case 1:
        new_pos=file_ptr->f_pos+offset;
        break;
    }
if(new_pos>MAXLEN)
    new_pos=MAXLEN;
if(new_pos<0)
    new_pos=0;
file_ptr->f_pos=new_pos;
return(new_pos);
}

static struct file_operations vdg_fops={
    .owner=THIS_MODULE,
    .open=vdg_open,
    .release=vdg_close,
    .read=vdg_read,
    .write=vdg_write,
    .llseek=vdg_lseek
    };

static int __init vdg_init(void)
{
int major=250;
int minor=0;
first=MKDEV(major,minor);
if(alloc_chrdev_region(&first,0,1,"VDG")<0)
return(-1);
if((my_device_class_ptr = class_create("vdg_chardev_class")) ==NULL)
{
    unregister_chrdev_region(first,1);
    return(-1);
}
device_create(my_device_class_ptr,NULL,first,NULL,"vdg_chardev_class");
if(device_create(my_device_class_ptr,NULL,first,"hi","vdg_chardev")==NULL)
{
    class_destroy(my_device_class_ptr);
    unregister_chrdev_region(first,1);
    return(-1);
}
cdev_init(&my_char_dev,&vdg_fops);
if(cdev_add(&my_char_dev,first,1)==-1)
{
    device_destroy(my_device_class_ptr,first);
    class_destroy(my_device_class_ptr);
    unregister_chrdev_region(first,1);
    return(-1);
}
printk(KERN_INFO "Welcome By VDG : Linux Character Device Driver Is Successfully Registered. \n");
return(0);
}

static void __exit vdg_exit(void)
{
cdev_del(&my_char_dev);
device_destroy(my_device_class_ptr,first);
class_destroy(my_device_class_ptr);
unregister_chrdev_region(first,1);
printk(KERN_INFO "Goodbye By VDG: Linux Character Device Driver Is Successfully Unregistered. \n");
}

module_init(vdg_init);
module_exit(vdg_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aashish Kumar <aashishkumar2k0@gmail.com>");
MODULE_DESCRIPTION("VDG: LINUX Character Driver");