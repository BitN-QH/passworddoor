#ifndef _SCANKEY_H
#define _SCANKEY_H

#include "public.h"

sbit K1 = P3 ^ 0;
sbit K2 = P3 ^ 1;
sbit K3 = P3 ^ 2;
sbit K4 = P3 ^ 3;

extern u8 KEY;
extern u8 KEY1;
extern u8 KEY2;

u8 getKeyNum();
void getIr();

#endif