#ifndef CHARDEV H
#define CHARDEV H

#include<linux/ioctl.h>

#define MAJOR_NUM 115

#define IMU_ACC _IOR(MAJOR_NUM, 0, char *)
#define IMU_ACC_X _IOR(MAJOR_NUM, 1, char *)
#define IMU_ACC_Y _IOR(MAJOR_NUM, 2, char *)
#define IMU_ACC_Z _IOR(MAJOR_NUM, 3, char *)
#define IMU_STANDBY _IOR(MAJOR_NUM, 4, char *)
#define IMU_MEASURE _IOR(MAJOR_NUM, 5, char *)


#define DEVICE_FILE_NAME "/dev/adxl"

#endif

