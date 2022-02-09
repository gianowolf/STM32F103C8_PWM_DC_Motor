#include "Controller.h"

#include "WaterLevelSensor.h"

static uint16_t water_level;

void Controller_Init()
{
}

void Controller_CatDetected()
{
	WaterBomb_StartPump();
	//Imprimir("I tawt I taw a puddy tat");
}

void Controller_CriticalWaterLevel()
{
	WaterBomb_StopPump();
	Leds_WaterLevel_On();
	//Imprimir("Fill with water to start pump");
}

void Controller_LowWaterLevel()
{
	//Imprimir("Low Water Level");
	Leds_WaterLevel_On();
}

void Controller_Update(){
	water_level = WaterLevelSensor_GetWaterLevel();
	if (water_level < EMPTY_LEVEL) {
		Leds_WaterLevel_Empty();
		WaterBomb_StopPump();
	} else {
		if (water_level < LOW_LEVEL) {
			Leds_WaterLevel_Low();
		} else {
			Leds_WaterLevel_Normal();
		}
		if (CatProximitySensor_SenseProximity()) {
			WaterBomb_StartPump();
		} else {
			WaterBomb_StopPump();
		}
	}
}
