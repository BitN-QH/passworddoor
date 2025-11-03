#ifndef _PAMANAGE_H
#define _PAMANAGE_H

#include "public.h"

extern u8 PASSWORD[8];
extern u8 ALLPASSWORD[8];
extern u8 INPASSWORD[8];
extern u8 CHANGEPASSWORD[8];

u8 Judge();
u8 JudgeAdmin();

void PACHANGE();
void ADCHANGE();
void AdminChange();
void PasswordChange();
void PasswordInit();

#endif