#ifndef _DEEP_H
#define _DEEP_H

#include "public.h"

sbit BEEP = P2 ^ 5;

void Beep(u16 time, u16 fre);

#endif