#include "WaterLevelSensor.h"

uint16_t water_level

void WaterLevelSensor_init()
{

}

void WaterLevelSensor_config()
{

}

uint16_t WaterLevelSensor_getWaterLevel()
{
 return water_level;
}

void WaterLevelSensor_INTERRUPT_LowWaterLevel()
{
    FLAG_LOW_WATER_LEVEL = 1;
} 