#ifndef _LEDS_H
#define _LEDS_H

#define LED_G_port GPIOA
#define LED_G_pin 15
#define LED_Y_port GPIOA
#define LED_Y_pin 12
#define LED_R_port GPIOA
#define LED_R_pin 11

void Leds_Init(void);
void Leds_WaterLevel_Normal(void);
void Leds_WaterLevel_Low(void);
void Leds_WaterLevel_Empty(void);

#endif
