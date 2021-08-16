#include <linux/module.h>
#include <linux/fs.h>

#define MAJOR_NUMBER 99
#define DRIVER_NAME "charDriver"

static int open_chardev(struct inode *inode, struct file *file);
static int release_chardev(struct inode *inode, struct file *file);
static ssize_t read_chardev(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t write_chardev(struct file *file, const char __user *buf, size_t count, loff_t *offset);

struct file_operations f_ops = {
    .owner   = THIS_MODULE,
    .open    = open_chardev,
    .release = release_chardev, 
    .read    = read_chardev,
    .write   = write_chardev

};

static int num = 10;

module_param(num, int, 0);

static int hello_init(void) {
    int err;
    printk(KERN_ALERT "Hello! Num = %d\n", num);

    err = register_chrdev(MAJOR_NUMBER, DRIVER_NAME, &f_ops);

    if (err)
        printk("register_chrdev: error.\n");
    else
        printk("register_chrdev: success.\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_ALERT "Good bye!! Num = %d\n", num);
    unregister_chrdev(MAJOR_NUMBER, DRIVER_NAME);
    printk("unregister_chrdev: char dev removed");
}


static int open_chardev(struct inode *inode, struct file *file) {
    static int device_access_cnt = 0;
    printk("Device accessed %d times.\n", ++device_access_cnt);
    return 0;
}

static int release_chardev(struct inode *inode, struct file *file) {
    printk("Device released.\n");
    return 0;
}

static ssize_t read_chardev(struct file *file, char __user *buf, size_t count, loff_t *offset) {
    printk("Reading...\n");
    return 0;
}
static ssize_t write_chardev(struct file *file, const char __user *buf, size_t count, loff_t *offset) {
    printk("Writing...\n");
    return count;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rpc3_rlo3");