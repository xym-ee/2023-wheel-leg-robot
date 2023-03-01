#include "controltask/motion.h"


#include "iotask/imu.h"
#include "iotask/sbus.h"
#include "iotask/motor_can.h"

#include "controltask/pid.h"


#define sgn(n)	((double)(n>=0 ? 1.0f:-1.0f))


#include <math.h>

/*--------------------------  数据处理线程  ---------------------------*/

static void motion_thread_entry(void *parameter)
{
	double e1 = 0.0;
	double e2 = 0.0;

	double e1_l = 0.0;
	
	double s;
	
	double torque_left;
	double torque_right;
	
    while (1)
    {
		/*---------------------------- 数据输入 --------------------------*/
        e1 = imu.roll*3.141593/1800; //-200~200
		
		/*---------------------------- 控制算法 --------------------------*/
		e2 = (e1 - e1_l)/0.008;
		
		s = e1 + e2;
		
		torque_left = -0.0177*2000*(-e2 - sqrt(fabs(s)) * sgn(s));
		
		torque_right = -torque_left;
		
		e1_l = e1;

		/*---------------------------- 数据输出 --------------------------*/
		/* 直立输出 */
		
		rt_kprintf("%d\n", (rt_int16_t)torque_left);
		
//		motor.left.control.torque  = torque_left;
//		motor.right.control.torque = torque_right;
		
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



