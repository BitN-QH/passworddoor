#include "stepmotor.h"

u8 Motor = 3;
/*******************************************************************************
* 函 数 名       : step_motor_28BYJ48_send_pulse
* 函数功能		 : 输出一个数据给ULN2003从而实现向步进电机发送一个脉冲
* 输    入       : step：指定步进序号，可选值0~7
				   dir：方向选择,1：顺时针,0：逆时针
* 输    出    	 : 无
*******************************************************************************/
void step_motor_28BYJ48_send_pulse(u8 step,u8 dir)
{
	u8 temp=step;
	
	if(dir==0)	//如果为逆时针旋转
		temp=7-step;//调换节拍信号
	switch(temp)//8个节拍控制：A->AB->B->BC->C->CD->D->DA
	{
		case 0: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=0;break;
		case 1: IN1_A=1;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 2: IN1_A=0;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 3: IN1_A=0;IN2_B=1;IN3_C=1;IN4_D=0;break;
		case 4: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=0;break;
		case 5: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=1;break;
		case 6: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=1;break;
		case 7: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=1;break;
		default: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=0;break;//停止相序	
	}			
}