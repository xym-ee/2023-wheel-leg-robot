/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



#include "iotask/motor_can.h"

#include "controltask/lpf.h"

#include "iotask/imu.h"


int main(void)
{
//	while(1)
//	{
//		rt_kprintf("l %d\n", motor.left.sensor.speed);
//		rt_kprintf("r %d\n", motor.right.sensor.speed);
//		
//		rt_thread_mdelay(500);
//	
//	
//	}
	
	
//	lpf_t lpf;
//	
//	rt_int32_t pitch;
//	double pitch_lpf;
//	
//	rt_int32_t pitch111;
//	
//	while(1)
//	{
//		pitch = imu.roll;
//		
//		pitch_lpf = lpf_output(&lpf, ((double)pitch)/10.0);
//		
//		pitch111 = pitch_lpf * 10;
//		
//		rt_kprintf("a=%d.%d,b=%d.%d,", pitch/10, pitch%10, pitch111/10, pitch111%10);
//		
//		rt_thread_mdelay(5);
//	}
	
	return RT_EOK;
}
