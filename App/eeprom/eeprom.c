#include "eeprom.h"
#include "pamanage.h"
#include "24c02.h"

void PARead()
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		ALLPASSWORD[i] = at24c02_read_one_byte(i);
	}
	for (i = 8; i < 16; i++)
	{
		PASSWORD[i - 8] = at24c02_read_one_byte(i);
	}
}

void PAWrite()
{
	u8 i = 8;
	for (i = 8; i < 16; i++)
	{
		at24c02_write_one_byte(i, PASSWORD[i - 8]);
	}
}

void ADPAWrite()
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		at24c02_write_one_byte(i, ALLPASSWORD[i]);
	}
}