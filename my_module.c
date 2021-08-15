#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rpc3_rlo3");


static int num = 10;

module_param(num, int, 0);

static int hello_init(void) {
    printk(KERN_ALERT"Hello! Num = %d\n", num);
    return 0;
}


static void hello_exit(void) {
    printk(KERN_ALERT"Good bye!! Num = %d\n", num);
}

module_init(hello_init);
module_exit(hello_exit);

