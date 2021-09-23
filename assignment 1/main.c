#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include <asm/uaccess.h>
#include<linux/random.h>

#include "aschrdev.h"		//header file containing definitions such as ioctl no.s, device path, device numbers

static dev_t first;
static struct cdev c_dev;
static struct class *cls;

	/*
	 * cat command is needed to run once to open the file as in my_open functionality
	 * there is only a printk statement. Else the below snippet can be used which is taken
	 * from https://github.com/electroons/G547/blob/master/IOCTL/chardev2.c
	 
	 	#ifdef DEBUG
			printk(KERN_INFO "device_open(%p)\n", file);
		#endif
		    if (Device_Open)
			return -EBUSY;

		    Device_Open++;
		    
		    Message_Ptr = Message;
		    try_module_get(THIS_MODULE);
		    return SUCCESS;
	 */

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar: open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Mychar: close()\n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Mychar: read()\n");
	return 0;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
    int i;
    int ret_val_;
    unsigned char j[2];

    /*
     * Switch according to the ioctl called
     */
    switch (ioctl_num) {
    	/*
    	 * The accelerometer, magnetometer and gyroscope of
    	 * the IMU(MPU9255) provide 16 bit data i.e. 2 bytes. 
    	 * Here random number of 2 bytes is generated. There
    	 * are 9 such cases (acc_x,acc_y,acc_z,gyro_x,gyro_y,
    	 * gyro_z,mag_x,mag_y,mag_z).
    	 */
    case IMU_ACC_X:
    	/*
         * Give the current message to the calling process -
         * the parameter we got is a pointer, fill it.
         */
        i = my_read(file, (char *)ioctl_param, 2, 0);

        /*
         * Put a zero at the end of the buffer, so it will be
         * properly terminated
         */
        get_random_bytes(j,1);					//generating 8bit random data
        get_random_bytes(j+1,1);					//generating 8bit random data
        printk(KERN_INFO "%u %u \n",j[0],j[1]);			//printing the numbers on kernel log to check(debug) if the bits sent are the same
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);	//sending data from kernel space to user space, 2 defines the number of bytes which are sent
    	break;
    case IMU_ACC_Y:
    	get_random_bytes(j,1);			
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_ACC_Z:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_GYRO_X:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_GYRO_Y:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_GYRO_Z:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_MAGNET_X:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_MAGNET_Y:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_MAGNET_Z:
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    case IMU_PRESS:
    	/*
     	 * For pressure sensor(BPU280) data field is of 10 bits.
     	 * So 16 bit random number is generated and its last 6 bits
     	 * are truncated.
     	 */
    	get_random_bytes(j,1);
        get_random_bytes(j+1,1);
        j[1] &= 0x03;								//Last 6 bits are masked as the data is of 10bits.
        printk(KERN_INFO "%u %u \n",j[0],j[1]);
        ret_val_ = copy_to_user((char *)ioctl_param + i,j,2);
    	break;
    }

    return 0;
}

static struct file_operations fops = 
{
  .owner	= THIS_MODULE,
  .open	= my_open,
  .release	= my_close,
  .read	= my_read,
  .unlocked_ioctl = device_ioctl
};

static int __init mychar_init(void)
{
	printk(KERN_INFO "Hello: mychar driver registered");
	if (alloc_chrdev_region(&first,0,1,"BITS_PILANI") < 0)
	{
		return -1;
	}
	 
	if ((cls = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first,1);
		return -1;
	}
	
	if (device_create(cls, NULL, first, NULL, "imu_char") == NULL)		//imu_char device file creation
	{
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}
	
	cdev_init(&c_dev, &fops);
	if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cls,first);
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}  
	return 0;
}

static void __exit mychar_exit(void)
{
		cdev_del(&c_dev);
		device_destroy(cls,first);
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		printk(KERN_INFO "Bye mychar driver unregistered\n\n");
		
}

module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHINAV PARIHAR");
MODULE_DESCRIPTION("This is 4 step module for first charachter driver");
