#ifndef _WATER_LEVEL_SENSOR_H
#define _WATER_LEVEL_SENSOR_H

#include <stm32f103x6.h>               
#include <stdint.h>

#define CRITICAL_LEVEL 1000
#define MINIMUM_LEVEL 3000

void WaterLevelSensor_Init(void);
void WaterLevelSensor_SenseWaterLevel(void);
uint16_t WaterLevelSensor_GetWaterLevel(void);

#endif
#ifndef _SEOS_H
#define _SEOS_H

#include <inttypes.h>

#endif