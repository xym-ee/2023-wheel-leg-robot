#ifndef __PID_H__
#define __PID_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


typedef struct 
{
    double ref;
    double feedback;
    double output;

    double kp;
    double ki;
    double kd;

    double out_lim;

    double int_lim;
    double int_boundary;

    double err;
    double err1;
    double err_sum;
} controller_t;


double controller_output(controller_t* controller, double ref, double feedback);

void controller_set_pid_parameter(controller_t* controller, double kp, double ki, double kd);

void controller_set_output_limit(controller_t* controller, double limit);


#endif



