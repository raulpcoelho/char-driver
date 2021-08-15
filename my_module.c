#include <linux/module.h>
#include <linux/fs.h>

#define MAJOR_NUMBER 99
#define DRIVER_NAME "charDriver"

struct file_operations f_ops;

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

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rpc3_rlo3");