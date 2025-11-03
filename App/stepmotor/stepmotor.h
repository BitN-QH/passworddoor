#ifndef _stepmotor_H
#define _stepmotor_H

#include "REGX52.H"
#include "public.h"

#define STEPMOTOR_MAXSPEED        1  
#define STEPMOTOR_MINSPEED        5  

sbit IN1_A=P1^0;
sbit IN2_B=P1^1;
sbit IN3_C=P1^2;
sbit IN4_D=P1^3;

extern u8 Motor;

void step_motor_28BYJ48_send_pulse(u8 step,u8 dir);

#endif
