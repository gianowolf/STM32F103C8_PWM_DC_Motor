#ifndef _WATER_LEVEL_SENSOR_H
#define _WATER_LEVEL_SENSOR_H

#include <stm32f103x6.h>               
#include <stdint.h>

void WaterLevelSensor_Init(void);
uint16_t WaterLevelSensor_GetWaterLevel(void);

#endif
