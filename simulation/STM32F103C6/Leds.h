#ifndef _LEDS_H
#define _LEDS_H

#include <stm32f103x6.h>

#define LED_G_clock RCC_APB2ENR_IOPAEN
#define LED_G_port GPIOA
#define LED_G_pin 6
#define LED_Y_clock RCC_APB2ENR_IOPAEN
#define LED_Y_port GPIOA
#define LED_Y_pin 12
#define LED_R_clock RCC_APB2ENR_IOPAEN
#define LED_R_port GPIOA
#define LED_R_pin 4

void Leds_Init(void);
void Leds_WaterLevel_Normal(void);
void Leds_WaterLevel_Low(void);
void Leds_WaterLevel_Empty(void);

#endif
