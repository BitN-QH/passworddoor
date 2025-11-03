#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "public.h"

sbit IRED = P3^2;

extern u8 timeNum;
extern u8 gired_data[4];
extern u8 IrValue[4];	 
//extern u8 Time;			 
extern u8 times;		 
extern u8 isIr;			  

void initEx0();
void timerInit();
void ired();
void ired_init();

#endif