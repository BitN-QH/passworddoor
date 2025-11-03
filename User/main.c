#include "mainline.h"
#include "eeprom.h"
#include "interrupt.h"

void main()
{
	ired_init();
	PARead();
	initEx0();
	while (1)
	{
		ShowNum();
	}
}
