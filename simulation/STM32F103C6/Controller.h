#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <stm32f103x6.h>               
#include <stdint.h>

#include "LCD.h"
#include "WaterBomb.h"
#include "Leds.h"

void Controller_Init(void);
void Controller_CatDetected(void);
void Controller_CriticalWaterLevel(void);
void Controller_LowWaterLevel(void);

#endif
