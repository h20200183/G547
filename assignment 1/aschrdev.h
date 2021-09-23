/*
 *  aschrdev.h - the header file with the ioctl definitions.
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (main.c) and the process calling ioctl (userapp.c)
 */

#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100							//used as magic number for our ioctl calls

#define IMU_ACC_X _IOR(MAJOR_NUM, 0, char *)				//send acceleration x axis data
#define IMU_ACC_Y _IOR(MAJOR_NUM, 1, char *)				//send acceleration y axis data
#define IMU_ACC_Z _IOR(MAJOR_NUM, 2, char *)				//send acceleration z axis data
#define IMU_GYRO_X _IOR(MAJOR_NUM, 3, char *)				//send magnetometer x axis data
#define IMU_GYRO_Y _IOR(MAJOR_NUM, 4, char *)				//send magnetometer y axis data
#define IMU_GYRO_Z _IOR(MAJOR_NUM, 5, char *)				//send magnetometer z axis data
#define IMU_MAGNET_X _IOR(MAJOR_NUM, 6, char *)			//send gyroscope x axis data
#define IMU_MAGNET_Y _IOR(MAJOR_NUM, 7, char *)			//send gyroscope y axis data
#define IMU_MAGNET_Z _IOR(MAJOR_NUM, 8, char *)			//send gyroscope z axis data
#define IMU_PRESS _IOR(MAJOR_NUM, 9, char *)				//send pressure data

/*
 * _IOR means that we're creating an ioctl command
 * number for passing information from a user process
 * to the kernel module.
 *
 * The first arguments, MAJOR_NUM, is the major device
 * number we're using.
 *
 * The second argument is the number of the command
 * (there could be several with different meanings).
 *
 * The third argument is the type we want to get from
 * the process to the kernel.
 */


#define DEVICE_FILE_NAME "/dev/imu_char"				//defining device file path

#endif
