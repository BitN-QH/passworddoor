#include "mainline.h"
#include "stepmotor.h"
#include "pamanage.h"
#include "interrupt.h"
#include "scankey.h"
#include "beep.h"
#include "smg.h"

u8 DATA[8] = {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
//u8 DATA[8] = {0x39, 0x3f, 0x5e, 0x79, 0x40, 0x40, 0x40, 0x40};

u8 TIME[2] = {0x7d, 0x3f};
u8 K = 0;
u8 CountDown[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
u8 ERROR = 0;
u8 PASS[8] = {0xce,0xee,0xb6,0xb6,0x00,0x00,0x00,0x00};//1100 1110 1110 1110 1011 0110 1011 0110
u8 step = 0;
u16 FLAG = 3000;

void Init()
{
	DATA[0] = 0x40;
	DATA[1] = 0x40;
	DATA[2] = 0x40;
	DATA[3] = 0x40;
	DATA[4] = 0x40;
	DATA[5] = 0x40;
	DATA[6] = 0x40;
	DATA[7] = 0x40;
	PasswordInit();
	K = 0;
}

void ErrorAction()
{
	timerInit();
	while (SEC != 0)
	{
		CountDown[0] = gsmg_code[SEC / 10];
		CountDown[1] = gsmg_code[SEC % 10];
		smg_display(CountDown, 1);
		KEY = getKeyNum();
		if (KEY != 16 || KEY1 != 16)
		{
			if (KEY == 15 || KEY1 == 15)
			{
				if (JudgeAdmin())
				{
					Init();
					SEC = 0;
					TR0 = 0;
					ET0 = 0;
					return;
				}
				else
				{
					Init();
				}
			}
			if (KEY < 10)
			{
				INPASSWORD[K] = KEY;
				K++;
				if (K == 9)
				{
					K = 0;
					Init();
				}
			}
		}
	}
	if (SEC == 0 || SEC > 60)
	{
		TR0 = 0;
		ET0 = 0;
		return;
	}
	KEY1 = 16;
}

void Back()
{
	if (K != 0)
	{
		K--;
		CHANGEPASSWORD[K] = 0;
		DATA[K] = 0x40;
	}
}

void PassAction()
{

	Init();
	timerInit();
	Motor = 3;
	FLAG = 3000;
	while (FLAG--)
	{
		step_motor_28BYJ48_send_pulse(step++, 0);
		if (step == 8)
			step = 0;
		delay_ms(1);
	}
	FLAG = 3000;
	delay_ms(2000);
	while (FLAG--)
	{
		step_motor_28BYJ48_send_pulse(step++, 1);
		if (step == 8)
			step = 0;
		delay_ms(1);
	}
	Motor = 3;
	SEC = 60;
	TR0 = 0;
	ET0 = 0;
}

void UPDATA()
{
	u8 i = 0;
	KEY = getKeyNum();
	getIr();
	if (KEY == 16 && KEY1 == 16 && KEY2 == 16)
		return;
	else
	{
		if (KEY == 15 || KEY1 == 0x0f || KEY2 == 15)
		{
			KEY1 = 16;
			if (Judge())
			{
				ERROR = 0;
				KEY2 = 16;
				PassAction();
				return;
			}
			else
			{
				ERROR++;
				Beep(800, 10);
				Init();
			}
		}
		if (ERROR == 3)
		{
			ERROR = 0;
			ErrorAction();
			SEC = 60;
			Init();
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
		if (KEY == 101 || KEY1 == 0x0a || KEY2 == 101)
		{
			KEY1 = 16;
			PasswordChange();
		}
		if (KEY == 103 || KEY1 == 0x0b || KEY2 == 103)
		{
			KEY1 = 16;
			AdminChange();
		}
		if (KEY < 10 || KEY1 < 10 || KEY2 < 10)
		{
			if (KEY2 != 16)
			{
				DATA[K] = gsmg_code[KEY2];
				INPASSWORD[K] = KEY2;
				KEY2 = 16;
			}
			else if (KEY1 != 16)
			{
				DATA[K] = gsmg_code[KEY1];
				INPASSWORD[K] = KEY1;
				KEY1 = 16;
			}
			else
			{
				DATA[K] = gsmg_code[KEY];
				INPASSWORD[K] = KEY;
				KEY = 16;
			}
			K++;
			if (K == 9)
			{
				K = 0;
				Init();
			}
		}
	}
}

void ShowNum(void)
{
	UPDATA();
	smg_display(DATA, 1);
}