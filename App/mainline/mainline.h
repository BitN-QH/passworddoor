#ifndef _MAINLINE_H
#define _MAINLINE_H

#include "public.h"

extern u8 DATA[8];
extern u8 TIME[2];
extern u8 K;
extern u8 CountDown[8];
extern u8 ERROR;
extern u8 step;
extern u16 FLAG;

void Init();
void ErrorAction();
void PassAction();
void UPDATA();
void ShowNum();
void Back();

#endif