#include "adxl.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/gpio.h>                 
#include <linux/interrupt.h>
#include <linux/workqueue.h>

#define DEVICE_NAME "adxl"
#define MAJOR_NO 115


#define REG_DEVID 0x00
#define REG_DATA_FORMAT 0x31			//Address for data format register
#define REG_POWER_CTL 0x2D			//power control regiter address
#define REG_DATAX0 0x32				//register which contain adxl345 data 0x32-0x37
#define REG_DATAX1 0x33
#define REG_DATAY0 0x34
#define REG_DATAY1 0x35
#define REG_DATAZ0 0x36
#define REG_DATAZ1 0x37

struct class *cls;
static struct i2c_client * my_client;
struct i2c_adapter * my_adap;
static dev_t first;
static struct cdev c_dev;
static u16 axis_data[6];


static u16 adxl_read(struct i2c_client *client, u8 reg)
{
	int ret;
	ret = i2c_smbus_read_word_data(client, reg);
	if (ret < 0)
		dev_err(&client->dev,
			"can not read register, returned %d\n", ret);

	return (u16)ret;
}

static int adxl_write(struct i2c_client *client, u8 reg, u8 data)
{
	int ret;
	ret = i2c_smbus_write_byte_data(client, reg, data);
	if (ret < 0)
		dev_err(&client->dev,"can not write register, returned %d\n", ret);

	return ret;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off) {

	printk(KERN_INFO "Driver read()\n");
	axis_data[0] = adxl_read(my_client, REG_DATAX0);
	axis_data[1] = adxl_read(my_client, REG_DATAY0);
	axis_data[2] = adxl_read(my_client, REG_DATAZ0);
	return 0;
}


static int my_open(struct inode *i, struct file *f)
{
	  printk(KERN_INFO "Driver: open()\n");
	    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	  printk(KERN_INFO "Driver: close()\n");
	    return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf,
		   size_t len, loff_t *off)
{
	  printk(KERN_INFO "Driver: write()\n");
	    return len;
}


/********IOCTL*********/
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
    int i,ret_val;
    u8 j;
    switch (ioctl_num) {

    case IMU_ACC:							//gets acceleration value for all 3 axis
        i = my_read(file, (char *)ioctl_param, 6, 0);
	ret_val = copy_to_user((char *)ioctl_param + i, axis_data,6);
    	break;
    case IMU_ACC_X:							//gets acceleration value for x axis
        i = my_read(file, (char *)ioctl_param, 6, 0);
	ret_val = copy_to_user((char *)ioctl_param + i, axis_data,2);
	break;
    case IMU_ACC_Y:							//gets acceleration value for y axis
        i = my_read(file, (char *)ioctl_param, 6, 0);
	ret_val = copy_to_user((char *)ioctl_param + i, axis_data+1,2);
	break;
    case IMU_ACC_Z:							//gets acceleration value for z axis
        i = my_read(file, (char *)ioctl_param, 6, 0);
	ret_val = copy_to_user((char *)ioctl_param + i, axis_data+2,2);
	break;
    case IMU_STANDBY:							//makes adxl go into standby mode
	j = adxl_read(my_client,REG_POWER_CTL);
	j = j & (0<<3);
	adxl_write(my_client, REG_POWER_CTL, j);
	break;
    case IMU_MEASURE:							//makes adxl go into measurement mode
	j = adxl_read(my_client,REG_POWER_CTL);
	j = j | (1<<3);
	adxl_write(my_client, REG_POWER_CTL, j);
	break;
    	}
    return 0;
}

static struct file_operations fops = {.read = my_read,				//file operations mapping
						.owner = THIS_MODULE,
						.open = my_open,
						.release = my_close,
						.write = my_write,
						.unlocked_ioctl=device_ioctl};



static int __init adxl_init(void)
{
	u8 readvalue,temp;
        printk(KERN_INFO "---ADXL345 Accelerometer!---\n");

        if (alloc_chrdev_region(&first, 0, 1, DEVICE_NAME) < 0) 
	{
		return -1;
        }

	if ((cls = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		unregister_chrdev_region(first,1);
		return -1;
	}

	if (device_create(cls, NULL, first, NULL, "adxl") == NULL)		//adxl device file creation
	{
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}

	cdev_init(&c_dev,&fops);
	if (cdev_add(&c_dev, first,1) == -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}

	my_adap = i2c_get_adapter(1); 						// 1 means i2c-1 bus
	if (!(my_client = i2c_new_dummy_device(my_adap, 0x53))){		
		printk(KERN_INFO "Couldn't acquire i2c slave");
		unregister_chrdev(MAJOR_NO, DEVICE_NAME);
		device_destroy(cls, first);
		class_destroy(cls);
		return -1;
	}

	temp = adxl_read(my_client,REG_POWER_CTL);
	temp = temp & (0<<3);							//Standby mode (recommended to put adxl in standby mode when setting modes and changing configurations)
	adxl_write(my_client, REG_POWER_CTL, temp);

	readvalue = adxl_read(my_client,0x00);
	if (readvalue == (0b11100101)) {					//checking and comparing the id of adxl
		printk("Accelerometer detected, value = %d\r\n",readvalue);
	}

	temp = adxl_read(my_client,REG_DATA_FORMAT);
	temp = temp | (1<<2);							//Data format is made left justified by writing to the justify bit of data format register
	adxl_write(my_client, REG_DATA_FORMAT, temp);

	temp = adxl_read(my_client,REG_POWER_CTL);
	temp = temp | (1<<3);							//Start measurement(removed from standby mode)
	adxl_write(my_client, REG_POWER_CTL, temp);

	return 0;
}


static void __exit adxl_exit(void)
{
        printk(KERN_INFO "ADXL: Removing module");


	i2c_unregister_device(my_client);
        cdev_del(&c_dev);
 	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
}

module_init(adxl_init);
module_exit(adxl_exit);

MODULE_DESCRIPTION("driver");
MODULE_AUTHOR("Sahil Abhinav");
MODULE_LICENSE("GPL");
