#include "scankey.h"
#include "interrupt.h"

u8 KEY = 16;
u8 KEY1 = 16;
u8 KEY2 = 16;

u8 getKeyNum()
{
	u8 key = 16;
	P1 = 0X0F;
	if (!(K1 && K2 && K3 && K4))
	{
		delay_ms(10);
		if (K1 == 0)
			return 102;
		if (K2 == 0)
			return 101;
		if (K3 == 0)
			return 103;
		if (K4 == 0)
			return 104;
	}
	if (P1 != 0X0F)
	{
		delay_ms(10);
		if (P1 != 0X0F)
		{
			if (P1 == 0x07)
			{
				key = 0;
			}
			else if (P1 == 0x0B)
			{
				key = 1;
			}
			else if (P1 == 0x0D)
			{
				key = 2;
			}
			else if (P1 == 0x0E)
			{
				key = 3;
			}
			P1 = 0XF0;
			if (P1 == 0x70)
			{
				key = key + 0;
			}
			else if (P1 == 0xB0)
			{
				key = key + 4;
			}
			else if (P1 == 0xD0)
			{
				key = key + 8;
			}
			else if (P1 == 0xE0)
			{
				key = key + 12;
			}
			while (P1 != 0XF0);
		}
	}
	return key;
}

void getIr()
{
		if(isIr == 0) 			
		{
	 	switch(gired_data[2])			
	 	{
	 	  case 0x16:
				KEY2 = 0;
				isIr = 1;			 
		  	break;
		case 0x0c:
				KEY2 = 1;
				isIr = 1;	
		  	break;
		case 0x18:
				KEY2 = 2;
				isIr = 1;	
		  	break;
		case 0x5e:
				KEY2 = 3;
				isIr = 1;	
		  	break;
		case 0x08:
				KEY2 = 4;
				isIr = 1;	
		  	break;
		case 0x1c:
				KEY2 = 5;
				isIr = 1;	
		  	break;
		case 0x5a:
				KEY2 = 6;
				isIr = 1;	
		  	break;
		case 0x42:
				KEY2 = 7;
				isIr = 1;			
		  	break;
		case 0x52:
				KEY2 = 8;
				isIr = 1;	
		  	break;
		case 0x4a:
				KEY2 = 9;
				isIr = 1;	
		  	break;

			case 0x45:
				KEY2 = 15;
				isIr = 1;	
		  	break;
			case 0x19:
				KEY2 = 13;
				isIr = 1;	
		  	break;
			case 0x0d:
				KEY2 = 14;
				isIr = 1;	
		  	break;
			case 0x40:
				KEY2 = 101;
				isIr = 1;	
		  	break;
			case 0x43:
				KEY2 = 103;
				isIr = 1;	
		  	break;
			case 0x44:
				KEY2 = 104;
				isIr = 1;	
		  	break;
			
	 }
	}
	else
	{
		KEY2 = 16;
	}
}