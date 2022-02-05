#include "Controller.h"

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
