#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cred.h>

#define MAJOR_NUMBER 91
#define DRIVER_NAME "charDriver"
#define BUFFER_LEN 10

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
    printk("Device accessed %d time(s).\n", ++device_access_cnt);
    printk("user id: %d\n", current_uid().val);
    return 0;
}

static int release_chardev(struct inode *inode, struct file *file) {
    printk("Device released.\n");
    return 0;
}

static ssize_t read_chardev(struct file *file, char __user *buf, size_t count, loff_t *offset) {
	const char *string = "Read function from driver\n";
	size_t stringlen = strlen(string);
	static int read = 0;

	if (read) {
		read = 0;
		return 0;
	}

	if (count > stringlen)
		count = stringlen;

	if (copy_to_user(buf, string, count))
		return -EFAULT;
	else {
		read = 1;
		printk("Data copied to user space.\n");
	    printk("Reading done.\n");
	}

    return count;
}
static ssize_t write_chardev(struct file *file, const char __user *buf, size_t count, loff_t *offset) {
	char driver_mem[BUFFER_LEN];
	int err = 0;
	int bytes;

	if (count > BUFFER_LEN)
		bytes = BUFFER_LEN;
	else 
		bytes = count;

	err = copy_from_user(driver_mem, buf, bytes);
	if (err) 
		printk("Error while copying bytes from user space. Error cnt: %d\n", err);

	printk("%s has been written.", driver_mem);
    printk("Writing done.\n");
    return bytes;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rpc3_rlo3");