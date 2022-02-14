#include "CatProximitySensor.h"

uint32_t t, t0, distance;
extern uint8_t FLAG_cat_detected;

void sendTrigger(void);

void CatProximitySensor_Init()
{
	RCC->APB2ENR |= 0xFC;	   			/* enable clocks for GPIO */
	RCC->APB1ENR |= (1<<0);    			/* Enable TIM2 clock      */

	GPIOA->CRL   &= 0xFFFF00FF;			/* ANDing Mask */

	/* ECO SETUP */
	GPIOA->CRL |= 0x00000800;  			/* PA2: [T2C2] as input pull-up */
	GPIOA->ODR |= 1<<2;	
	TIM2->CCMR2 = 0x001; 				/* Pin TIM2_CH3 as input for channel 3 */
	TIM2->CCER = 0x1 << 8; 				/* CC3P = 0 (rising), CC3E = 1 */
	TIM2->PSC = 1 - 1; 					/* Prescaler = 1 for Proteus simulation */
	TIM2->ARR = 50000-1;

	/* TRIGGER SETUP */
	GPIOA->CRL |= 0x00003000; 			/* PA3: as Output mode*/
	GPIOA->BRR  = (1<<3);           	/* make PA pin 3 low */
	
	FLAG_cat_detected = 0;	
}

uint8_t CatProximitySensor_SenseProximity() {
	sendTrigger();
	TIM2->CR1 = 1; 					/* Start counting up */

	TIM2->CCER = 0x1 << 8;  		/* CC3P = 1 (RISING), CC3E = 1 */
	while((TIM2->SR &(1<<3)) == 0); /* Wait until the CC3IF flag sets */
	t0 = TIM2->CCR3;				/* Get t0 */

	TIM2->CCER = 0x3 << 8; 			/* CC3P = 1 (FALLING), CC3E = 1 */
	while((TIM2->SR &(1<<3)) == 0); /* Wait until the CC3IF flag sets */
	t = TIM2->CCR3; 				/* Get t */
	
	distance = CALIB * (t-t0);      /* d[cm] = error * (t-t0)/(f*c) */

	TIM2->CR1 = 0; 					/* Stop counting */
	TIM2->CNT = 0;					/* Reset counter */

	return (distance<TRIGGER_DISTANCE) ? 1 : 0;
}

void sendTrigger()
{
	GPIOA->BSRR = (1<<3); /* make the PA pin 3 high */
	Utils_Delay_us(10);
	GPIOA->BRR  = (1<<3); /* make the PA pin 3 low*/
	Utils_Delay_us(10); 
}
