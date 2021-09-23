/*
 *  userapp.c - the process to use ioctl's to control the kernel module
 */

#include "aschrdev.h"		//header file containing definitions such as ioctl no.s, device path, device numbers


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */

/*
 * Functions for the ioctl calls
 */

int ioctl_get_acc_x(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_ACC_X, &mesg);					//corresponding ioctl call is made

    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));	//the message is printed in the console received from the kernel space, it can be verified
    return 0;										//by comparing the bits printed in console with kernel logs
}
int ioctl_get_acc_y(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_ACC_Y,&mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_acc_z(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_ACC_Z, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_mag_x(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_MAGNET_X, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_mag_y(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_MAGNET_Y, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_mag_z(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_MAGNET_Z, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_gyro_x(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_GYRO_X, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_gyro_y(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_GYRO_Y, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}
int ioctl_get_gyro_z(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_GYRO_Z, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}


int ioctl_get_press(int file_desc)
{
    int ret_val;
    unsigned char mesg[2];
    ret_val = ioctl(file_desc, IMU_PRESS, &mesg);

    if (ret_val < 0) {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else
    	printf("%u %u, size of message is %ld \n",mesg[0],mesg[1],sizeof(mesg));
    return 0;
}


/*
 * Main - Call the ioctl functions
 */
int main()
{
    int file_desc, ret_val;
    char *msg = "Message passed by ioctl\n";

    file_desc = open(DEVICE_FILE_NAME, 0);						//device file is opened
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }
    else
    	printf("Device Opened \n");
    	
    ioctl_get_acc_x(file_desc);							//wrapper functions for the ioctl call are made						
    ioctl_get_press(file_desc);
 //   ioctl_get_acc_y(file_desc);
 //   ioctl_get_acc_z(file_desc);
 //   ioctl_get_mag_x(file_desc);
 //   ioctl_get_mag_y(file_desc);
 //   ioctl_get_mag_z(file_desc);
 //   ioctl_get_gyro_x(file_desc);
 //   ioctl_get_gyro_y(file_desc);
 //   ioctl_get_gyro_z(file_desc);
    

    close(file_desc);
    return 0;
}
