#include "WaterBomb.h"

uint8_t bomb_ENA;

void WaterBomb_Init()
{
	RCC->APB2ENR |= 0xFC;  	/* Enable GPIO clocks */
	RCC->APB1ENR |= (1<<1);	/* Enable TIM3 clock */

	GPIOA->CRL   &= 0x0FFFFFFF; 			 
	GPIOA->CRL   |= 0xB0000000;/* PA1 (ADC_IN1) as analog input   */ 

	TIM3->CCER = 0x1 << 4;	/* CC2P = 0   , CC2E = 1  */
	TIM3->CCMR1= 0x6800;	/* OC2M = PWM1, OC2PE = 1 */
	TIM3->CR1 = 0xA0; 		/* Auto reload preload enable, up-down counting mode */
	
	TIM3->PSC = 0;			/* prescaler = 1 */
	TIM3->ARR = 36000;		/* ARR = 36.000  */

	bomb_ENA = 0;
}

void WaterBomb_StartPump()
{
	if(bomb_ENA == 0)
	{
		TIM3->CCR2= 0;		/* Duty-Cycle = (0/36000)*100 */
		TIM3->EGR = 1;		/* UG = 1 (Generate Update)   */
		TIM3->CR1 |= 0x01;	/* Timer Enable (CEN = 1)     */
		bomb_ENA = 1;
	}

}

void WaterBomb_StopPump()
{
	if(bomb_ENA == 1)
	{
		TIM3->CCR2 = 0;
		bomb_ENA = 0;
	}
}

uint8_t WaterBomb_IsEnabled()
{
	return bomb_ENA;
}
