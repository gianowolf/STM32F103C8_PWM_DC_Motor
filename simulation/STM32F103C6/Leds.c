#include "Leds.h"

void Leds_Init(void)
{

}

void Leds_WaterLevel_Off(void)
{
}

void Leds_WaterLevel_On(void)
{
}

	//GPIOA->BRR = (1<<3); 
	//Utils_Delay_us(10);
	//GPIOA->BSRR   = (0<<3); 
	//Utils_Delay_us(10);


	//RCC->APB2ENR |= 0xFC;	   			/* enable clocks for GPIO */
	//RCC->APB1ENR |= (1<<0);    			/* Enable TIM2 clock      */

	//GPIOA->CRL   &= 0xF000FFFF;			/* ANDing Mask */

	/* TRIGGER SETUP */
	//GPIOA->CRL |= 0x00003000; 			/* PA3: as Output mode*/
	//GPIOA->BRR = (1<<3);           	/* make PA pin 3 low  */