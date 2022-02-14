#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <stm32f103x6.h>               
#include <stdint.h>

#include "LCD.h"
#include "WaterBomb.h"
#include "Leds.h"

#define LOW_LEVEL 50
#define NOT_LOW_LEVEL 60
#define EMPTY_LEVEL 10 // Level at wich the tank is considered empty
#define NOT_EMPTY_LEVEL 25

void Controller_Init(void);
void Controller_CatDetected(void);
void Controller_CriticalWaterLevel(void);
void Controller_LowWaterLevel(void);

#endif
