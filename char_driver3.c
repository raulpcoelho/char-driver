#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cred.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define MAJOR_NUMBER 91
#define DRIVER_NAME "charDriver"
#define BUFFER_LEN 20
#define DEVICE_NAME "mychardev"

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

dev_t device;
struct class *char_class = NULL;
struct cdev char_dev;

static int uevent(struct device *dev, struct kobj_uevent_env *env) {
	add_uevent_var(env, "DEVMODE=%#o", 0666);
	return 0;
}


static int hello_init(void) {
    int err;
    printk(KERN_ALERT "Hello!!");

	err = alloc_chrdev_region(&device, 0, 1, DRIVER_NAME);
    if (err)
        printk("alloc_chrdev_region: error.\n");
    else
        printk("alloc_chrdev_region: success.\n");

    char_class = class_create(THIS_MODULE, DRIVER_NAME);
    char_class->dev_uevent = uevent;
    cdev_init(&char_dev, &f_ops);
    char_dev.owner = THIS_MODULE;
    cdev_add(&char_dev, device, 1);
    device_create(char_class, NULL, device, NULL, DEVICE_NAME);
    printk("Device created.\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_ALERT "Good bye!!");

    device_destroy(char_class, device);
    class_unregister(char_class);
    class_destroy(char_class);
    unregister_chrdev_region(device, MINORMASK);

    printk("Device removed\n");
}


static int open_chardev(struct inode *inode, struct file *file) {
    static int device_access_cnt = 0;
    printk("Device accessed %d time(s).\n", ++device_access_cnt);
    printk("User ID: %d\n", current_uid().val);
    return 0;
}

static int release_chardev(struct inode *inode, struct file *file) {
    printk("Device released.\n");
    return 0;
}

static ssize_t read_chardev(struct file *file, char __user *buf, size_t count, loff_t *offset) {
	const char *string = "Read function from driver.\n";
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

	if (count < BUFFER_LEN)
		bytes = count;
	else 
		bytes = BUFFER_LEN;

	err = copy_from_user(driver_mem, buf, bytes);

	if (err) 
		printk("Error while copying bytes from user space. Error cnt: %d\n", err);
	driver_mem[bytes - 1] = '\0'; //end of string

	printk("Copied from user space: %s, length: %d", driver_mem, bytes - 1);
    printk("Writing done.\n");
    return bytes;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("rpc3_rlo3");