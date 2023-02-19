#include "controltask/motion.h"


#include "iotask/imu.h"
#include "iotask/sbus.h"
#include "iotask/motor_can.h"

#include "controltask/pid.h"


/*--------------------------  数据处理线程  ---------------------------*/

static void motion_thread_entry(void *parameter)
{
    /* velocity pd controller */
    double velocity_ref = 0.0;
    double velocity_feedback = 0.0;
    controller_t velocity_controller;

    controller_set_pid_parameter(&velocity_controller, 65.0, 0.0, 20.0);
    controller_set_output_limit(&velocity_controller, 3.0);

    /* angle pd controller */
    double angle_ref = 0.0;
    double angle_feedback = 0.0;
    controller_t angle_controller;

    controller_set_pid_parameter(&angle_controller, 7.0, 0, 60.0);
	controller_set_output_limit(&angle_controller, 1300.0);
	
	rt_int16_t torque_left;
	rt_int16_t torque_right;
	
    while (1)
    {
		/* angle pd controller.  */
        angle_feedback = imu.roll; //-200~200
		
        torque_left  = controller_output(&angle_controller, angle_ref, angle_feedback);
		torque_right = -torque_left;

		/* 直立输出 */
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
}

/* 导出命令 or 自动初始化 */
INIT_APP_EXPORT(motion_init);



