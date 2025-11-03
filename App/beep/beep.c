#include "beep.h"

void Beep(u16 hz, u16 fre)
{
	u8 t = 0;
	u16 time;
	for(t = 0;t < 2;t++)
	{
		time = hz;
	while (time--)
	{
		BEEP = !BEEP;
		delay_10us(fre);
	}
	delay_ms(200);
}
}
