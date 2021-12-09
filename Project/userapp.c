#include "adxl.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


int ioctl_get_acc(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    short int mesg[3];
    ret_val = ioctl(file_desc, IMU_ACC, &mesg);						//corresponding ioctl call is made
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	printf("X: %hi, Y: %hi, Z: %hi, size of message is %ld \n",mesg[0]>>6,mesg[1]>>6,mesg[2]>>6,sizeof(mesg));	//Message arithmetic right shifted by 6 bits as the data was left justified
        }
	return 0;										
}

int ioctl_get_acc_x(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    short int mesg[1];
    ret_val = ioctl(file_desc, IMU_ACC_X, &mesg);
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	//mesg[0] >> 6; mesg[1] >> 6; mesg[2] >> 6;
	printf("X: %hi , size of message is %ld \n",mesg[0]>>6,sizeof(mesg));
    }
	return 0;										
}

int ioctl_get_acc_y(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    short int mesg[1];
    ret_val = ioctl(file_desc, IMU_ACC_Y, &mesg);
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	printf("Y: %hi , size of message is %ld \n",mesg[0]>>6,sizeof(mesg));
    }
	return 0;										
}

int ioctl_get_acc_z(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    short int mesg[1];
    ret_val = ioctl(file_desc, IMU_ACC_Z, &mesg);
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	printf("Z: %hi , size of message is %ld \n",mesg[0]>>6,sizeof(mesg));
    }
	return 0;										
}

int ioctl_standby(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    int mesg[1];
    ret_val = ioctl(file_desc, IMU_STANDBY, &mesg);
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	printf("Entered Standby Mode\n");
    }
	return 0;										
}

int ioctl_measure(int file_desc)							//wrapper function for ioctl calls
{
    int ret_val;
    int mesg[1];
    ret_val = ioctl(file_desc, IMU_MEASURE, &mesg);
    
    if (ret_val < 0) {									//return value checked to see if ioctl call was succesful
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    else{
	printf("Entered Measurement Mode\n");
    }
	return 0;										
}


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
    	
    ioctl_get_acc(file_desc);								//wrapper functions for the ioctl call are made						
    ioctl_get_acc_x(file_desc);
    ioctl_get_acc_y(file_desc);
    ioctl_get_acc_z(file_desc); 
    ioctl_standby(file_desc);
    ioctl_measure(file_desc);    

    close(file_desc);
    return 0;
}
