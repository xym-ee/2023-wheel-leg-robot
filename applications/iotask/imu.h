#ifndef __IMU_H__
#define __IMU_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define IMU_UART       "uart2"


#define IMU_THREAD_PRIORITY         25
#define IMU_THREAD_STACK_SIZE       1024
#define IMU_THREAD_TIMESLICE        10



typedef struct 
{
	double roll;
	double pitch;
	double yaw;
} 
imu_t;

extern imu_t imu;

#endif



