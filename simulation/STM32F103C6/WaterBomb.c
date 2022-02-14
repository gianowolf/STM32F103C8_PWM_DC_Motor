#include "WaterBomb.h"

void WaterBomb_Init()
{
	RCC->APB2ENR |= 0xFC;  	/* Enable GPIO clocks */
	RCC->APB1ENR |= (1<<1);	/* Enable TIM3 clock */

	GPIOA->CRL &= 0x0FFFFFFF;
	GPIOA->CRL |= 0xB0000000;

	TIM3->CCER = 0x1 << 4;	/* CC2P = 0   , CC2E = 1  */
	TIM3->CCMR1= 0x6800;	/* OC2M = PWM1, OC2PE = 1 */
	TIM3->CR1 = 0xA0; 		/* Auto reload preload enable, up-down counting mode */
	
	TIM3->PSC = 1;			/* prescaler = 1 */
	TIM3->ARR = 36000;		/* ARR = 36.000  */

	TIM3->EGR = 1;		/* UG = 1 (Generate Update)   */
	TIM3->CR1 |= 0x00;	/* Timer Disabled (CEN = 0)     */
	TIM3->CCR2 = 36000;

}

void WaterBomb_StartPump()
{
	TIM3->CR1 |= 0x01;	/* Timer Enable (CEN = 1)     */
}

void WaterBomb_StopPump()
{
	TIM3->CR1 |= 0x00;	/* (CEN = 0) */
}
