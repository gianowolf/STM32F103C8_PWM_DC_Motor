#include "WaterLevelSensor.h"

uint32_t water_level;
extern uint8_t FLAG_low_water_level;
extern uint8_t FLAG_critical_water_level;

void WaterLevelSensor_Init()
{
	RCC->APB2ENR |= 0xFC | (1<<9) | (1<<14); /* enable locks for GPIo, ADC1 clock and usart1 */
	GPIOA->CRL   &= 0xFFFFFF0F; 			 /* PA1 (ADC_IN1) as analog input   */ 

	ADC1->CR2 = 1; /* ADON = 1 (power-up) */
	
	ADC1->SMPR2 = 1<<6; /* SMPR2.SMP = 001 */

	water_level = 0;
}

void WaterLevelSensor_SenseWaterLevel()
{
	ADC1->SQR3 = 2; /* channel 2 as the input */
	ADC1->CR2 = 1; /* ADON = 1 (start conversion) */
	while((ADC1->SR & (1<<1)) == 0); /* wait until the EOC flag is set) */
	water_level = ADC1->DR;

	/* 
	DEBUG

	if(water_level < MINIMUM_LEVEL)
	{
		if(water_level < CRITICAL_LEVEL)
		{
			FLAG_critical_water_level = 1;
		}
		else 
		{
			FLAG_low_water_level = 1;
		}
	}
	else
	{
		FLAG_critical_water_level = 0;
		FLAG_low_water_level = 0;
	}

	END DEBUG 
	*/
}

uint16_t WaterLevelSensor_GetWaterLevel()
{
	return 0;
}
