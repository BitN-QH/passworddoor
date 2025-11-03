#include "interrupt.h"
#include "scankey.h"
#include "stepmotor.h"
#include "pamanage.h"
#include "public.h"

u8 timeNum = 0;
u8 gired_data[4];
u8 IrValue[4];	 
u8 times;		 
u8 isIr = 1;			  

void initEx0()
{
	SCON = 0X50; // 0101 0000
	PCON = 0;
	TL1 = 253;
	TH1 = 253;
	TMOD = 0X20;
	ES = 1;
	EA = 1;
	TR1 = 1;
}

void DataAction() interrupt 4
{
	KEY1 = SBUF;
	RI = 0;
}

void timerInit() // TOMD = 0x01?¨¢?¡ã?¨¬????????
{
	TMOD &= 0xF0; // ????????4??(T0)
	TMOD |= 0x01; // ¡À?????4??(T1)??¡À?
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	TH0 = 0x4b;
	TL0 = 0xff;
}

void timerAction() interrupt 1
{
	TH0 = 0x4b;
	TL0 = 0xff;
	timeNum++;
	if (timeNum == 20)
	{
		timeNum = 0;
		SEC--;
		Motor--;
		if (SEC == -1)
		{
			SEC = 60;
			TR0 = 0;
			ET0 = 0;
		}
	}
}

void ired_init(void)
{
	IT0=1;
	EX0=1;
	EA=1;
	IRED=1;
}

void ired() interrupt 0
{
	u8 ired_high_time=0;
	u16 time_cnt=0;
	u8 i=0,j=0;
	isIr = 0;

	if(IRED==0)
	{
		time_cnt=1000;
		while((!IRED)&&(time_cnt))
		{
			delay_10us(1);
			time_cnt--;
			if(time_cnt==0)return;		
		}
		if(IRED)
		{
			time_cnt=500;
			while(IRED&&time_cnt)
			{
				delay_10us(1);
				time_cnt--;
				if(time_cnt==0)return;	
			}
			for(i=0;i<4;i++)
			{
				for(j=0;j<8;j++)
				{
					time_cnt=600;
					while((IRED==0)&&time_cnt)
					{
						delay_10us(1);
						time_cnt--;
						if(time_cnt==0)return;	
					}
					time_cnt=20;
					while(IRED)
					{
						delay_10us(10);
						ired_high_time++;
						if(ired_high_time>20)return;	
					}
					gired_data[i]>>=1;
					if(ired_high_time>=8)
						gired_data[i]|=0x80;
					ired_high_time=0;
				}
			}
		}
		if(gired_data[2]!=~gired_data[3])
		{
			for(i=0;i<4;i++)
				gired_data[i]=0;
			return;	
		}
	}		
}