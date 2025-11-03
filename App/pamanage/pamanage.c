#include "pamanage.h"
#include "scankey.h"
#include "mainline.h"
#include "eeprom.h"
#include "smg.h"

u8 PASSWORD[8] = {1, 2, 3, 4, 5, 6, 7, 8};
u8 ALLPASSWORD[8] = {1, 1, 1, 1, 1, 1, 1, 1};
u8 INPASSWORD[8] = {0};
u8 CHANGEPASSWORD[8] = {0};

void PasswordInit()
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		CHANGEPASSWORD[i] = 0;
		INPASSWORD[i] = 0;
	}
}

u8 JudgeAdmin()
{
	u8 i = 0;
	u8 flag = 1;
	for (i = 0; i < 8; i++)
	{
		if (INPASSWORD[i] != ALLPASSWORD[i])
		{
			flag = 0;
		}
	}
	return flag;
}

u8 Judge()
{
	u8 i = 0;
	u8 flag = 1;
	for (i = 0; i < 8; i++)
	{
		if (INPASSWORD[i] != PASSWORD[i] && INPASSWORD[i] != ALLPASSWORD[i])
		{
			flag = 0;
		}
	}
	return flag;
}

void ADCHANGE()
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		ALLPASSWORD[i] = CHANGEPASSWORD[i];
	}
}

void AdminChange()
{
	Init();
	while (1)
	{
		KEY = getKeyNum();
		getIr();
		if (KEY ==104 || KEY1 == 0x0c || KEY2 == 104)
		{
			KEY1 = 16;
			return;
		}
		if (KEY == 15 || KEY1 == 0x0f || KEY2 == 15)
		{
			KEY1 = 16;
			ADCHANGE();
			ADPAWrite();
			Init();
			return;
		}
		if (KEY == 14 || KEY1 == 0x0e || KEY2 == 14)
		{
			KEY1 = 16;
			Init();
		}
		if (KEY == 13 || KEY1 == 0x0d || KEY2 == 13)
		{
			KEY1 = 16;
			Back();
		}
		if (KEY < 10 || KEY1 < 10 || KEY2 < 10)
		{
			if (KEY2 != 16)
			{
				DATA[K] = gsmg_code[KEY2];
				CHANGEPASSWORD[K] = KEY2;
				KEY1 = 16;
			}
			else if (KEY1 != 16)
			{
				DATA[K] = gsmg_code[KEY1];
				CHANGEPASSWORD[K] = KEY1;
				KEY1 = 16;
			}
			else
			{
				DATA[K] = gsmg_code[KEY];
				CHANGEPASSWORD[K] = KEY;
				KEY = 16;
			}
			K++;
			if (K == 9)
			{
				K = 0;
				Init();
			}
		}
		smg_display(DATA, 1);
	}
}

void PACHANGE()
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		PASSWORD[i] = CHANGEPASSWORD[i];
	}
}

void PasswordChange()
{
	Init();
	while (1)
	{
		KEY = getKeyNum();
		getIr();
		if (KEY ==104 || KEY1 == 0x0c || KEY2 == 104)
		{
			KEY1 = 16;
			return;
		}
		if (KEY == 15 || KEY1 == 0x0f || KEY2 == 15)
		{
			KEY1 = 16;
			PACHANGE();
			PAWrite();
			Init();
			return;
		}
		if (KEY == 14 || KEY1 == 0x0e || KEY2 == 14)
		{
			KEY1 = 16;
			Init();
		}
		if (KEY == 13 || KEY1 == 0x0d || KEY2 == 13)
		{
			KEY1 = 16;
			Back();
		}
		if (KEY < 10 || KEY1 < 10 || KEY2 <10)
		{
			if (KEY2 != 16)
			{
				DATA[K] = gsmg_code[KEY2];
				CHANGEPASSWORD[K] = KEY2;
				KEY2 = 16;
			}
			else if (KEY1 != 16)
			{
				DATA[K] = gsmg_code[KEY1];
				CHANGEPASSWORD[K] = KEY1;
				KEY1 = 16;
			}
			else
			{
				DATA[K] = gsmg_code[KEY];
				CHANGEPASSWORD[K] = KEY;
				KEY = 16;
			}
			K++;
			if (K == 9)
			{
				K = 0;
				Init();
			}
		}
		smg_display(DATA, 1);
	}
}