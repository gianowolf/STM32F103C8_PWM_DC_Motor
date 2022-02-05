#ifndef _SEOS_H
#define _SEOS_H

/* MCU Device Header */
#include <stm32f103x6.h>

/* C Libraries */
#include <stdint.h>

/* Input Modules */
#include "CatProximitySensor.h"
#include "WaterLevelSensor.h"

/*Output Modules */
#include "WaterBomb.h"
#include "Leds.h"
#include "LCD.h"

/* Application Modules */
#include "Controller.h"

#define OVRF_SENSE_PROXIMITY 3
#define OVRF_SENSE_WATER_LEVEL 7

void SEOS_Boot(void);
void SEOS_Scheduler(void);
void SEOS_Dispatcher(void);
void SEOS_Sleep(void);

#endif
