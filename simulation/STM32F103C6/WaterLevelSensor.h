#ifndef _WATER_LEVEL_SENSOR_H
#define _WATER_LEVEL_SENSOR_H

#define CUBOID_TANK // Comment this line for cylindrical tank
// Use values in centimeters
// Cuboid tanks
#define TANK_WIDTH 10 // Not used for cylindrical tanks
#define TANK_LENGTH 10 // Not used for cylindrical tanks
// Cylindrical tanks
#define TANK_RADIUS 10 // Not used for cuboid tanks

#include <stm32f103x6.h>               
#include <stdint.h>

void WaterLevelSensor_Init(void);
uint16_t WaterLevelSensor_GetWaterLevel(void);

#endif
