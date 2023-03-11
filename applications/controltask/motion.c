#include "controltask/motion.h"


#include "iotask/imu.h"
#include "iotask/sbus.h"
#include "iotask/motor_can.h"

#include "controltask/pid.h"


/*--------------------------  控制  ---------------------------*/

static void motion_thread_entry(void *parameter)
{
    /* velocity pd controller */
    double velocity_ref = 0.0;
    double velocity_feedback = 0.0;
		
    controller_t velocity_controller;

    controller_set_pid_parameter(&velocity_controller, 0.0, 0.0, 0.0);
    controller_set_output_limit(&velocity_controller, 10.0);

    /* angle pd controller */
    double angle_ref = 0.0;
    double angle_feedback = 0.0;
	
	rt_uint8_t flag = 0;
	
    controller_t angle_controller_1;
    controller_set_pid_parameter(&angle_controller_1, 3.4, 0, 28.0);
	controller_set_output_limit(&angle_controller_1, 400.0);
	
    controller_t angle_controller_2;
    controller_set_pid_parameter(&angle_controller_2, 2.5, 0, 28.0);
	controller_set_output_limit(&angle_controller_2, 600.0);	
	
	/* 转向速度控制，PD，直接开环叠转矩也能用 */
	rt_int16_t torque;
	rt_int16_t torque_turn = 0;
	
	rt_int16_t torque_left;
	rt_int16_t torque_right;
	
	rt_thread_mdelay(3000);
	
    while (1)
    {
//		velocity_ref = (sbus.lv - SBUS_CH_OFFSET)*500/SBUS_CH_LENGTH;
//		
//		velocity_feedback = (motor.left.sensor.speed - motor.right.sensor.speed)/2.0;
//		
//		angle_ref = controller_output(&velocity_controller, velocity_ref, velocity_feedback);
		
		
		/* angle pd controller.  */
        angle_feedback = -imu.roll; //-200~200
		
		if ( (angle_feedback>-10) && (angle_feedback<10))
		{
			torque = controller_output(&angle_controller_1, angle_ref, angle_feedback);
		}
		else
		{
			torque = controller_output(&angle_controller_2, angle_ref, angle_feedback);
		}
		
		
		/* 叠加转向 */
        torque_left  = torque + torque_turn;
		torque_right = -(torque - torque_turn);
		

		/* 电机转矩输出 */
		motor.left.control.torque  = torque_left;
		motor.right.control.torque = torque_right;
		
		rt_thread_mdelay(8);
    }
}

//static void motion_thread_entry(void *parameter)
//{
//	rt_int32_t torque_left;
//	
//    while (1)
//    {
//		torque_left = sbus.lv;
//		
//		torque_left = (torque_left - SBUS_CH_OFFSET)*500/SBUS_CH_LENGTH;
//		
//		rt_kprintf("%d\n",torque_left);
//		
//		motor.left.control.torque = torque_left;
//		motor.right.control.torque = torque_left;
//		
//		rt_thread_mdelay(10);
//    }
//}

int motion_init(void)
{
    /* 创建 motion 线程 */
    rt_thread_t thread = rt_thread_create("motion", 
                                        motion_thread_entry, 
                                        RT_NULL, 
                                        MOTION_THREAD_STACK_SIZE, 
                                        MOTION_THREAD_PRIORITY, 
										MOTION_THREAD_TIMESLICE);
    
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
	
	return 0;
}

/* 导出命令 or 自动初始化 */
INIT_APP_EXPORT(motion_init);



