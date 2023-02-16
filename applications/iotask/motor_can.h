#ifndef __MOTOR_CAN_H__
#define __MOTOR_CAN_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define CAN_DEV_NAME       "can1"      /* CAN 设备名称 */


#define CAN_RX_PRIORITY         6
#define CAN_RX_STACK_SIZE       1024
#define CAN_RX_TIMESLICE        10


#define CAN_TX_PRIORITY         6
#define CAN_TX_STACK_SIZE       1024
#define CAN_TX_TIMESLICE        10



typedef struct {
    rt_int16_t  angle;
    rt_int16_t  speed;
    rt_int16_t  torque;
    rt_int16_t  voltage;
//    pid_t       pid;
} motor_data_t;

#endif



