#include "utils.h"

void Utils_Delay_ms(uint16_t t)
{
	volatile uint16_t l, i;
	for(i = 0 ; i < t ; i++)
	{
		for(l = 0; l < 6000 ; l++)
		{
		}
	}
}

void Utils_Delay_us(uint16_t t)
{
	volatile uint16_t l, i;
	for(i = 0 ; i < t ; i++)
	{
		for(l = 0; l < 12 ; l++)
		{
		}
	}
}
