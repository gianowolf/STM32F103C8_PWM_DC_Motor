#include "Seos.h"

/* Public Flags */
static volatile uint8_t FLAG_sense_proximity;
static volatile uint8_t FLAG_sense_water_level;

uint8_t FLAG_cat_detected;
uint8_t FLAG_low_water_level;
uint8_t FLAG_critical_water_level;
uint8_t FLAG_MOTOR = 0;

/* Private */
void seos_init(void);

uint32_t counter_motor;
static volatile uint8_t counter_sense_proximity;
static volatile uint8_t counter_sense_water_level;

void SysTick_Handler(void)
{
	SEOS_Scheduler();
}

void seos_init(void)
{
	/* Periodic Events FLAGS */
	FLAG_sense_proximity = 0;
	counter_sense_proximity = 0;
	FLAG_sense_water_level = 0;
	counter_sense_water_level = 0;

	/* Aperiodic Events FLAGS */
	FLAG_low_water_level = 0;
	FLAG_critical_water_level = 0;
	FLAG_cat_detected = 0;

	if(SysTick_Config(SystemCoreClock/10))
	{ /* Error handling */ }
}

void SEOS_Boot()
{
	seos_init();

	/* Init Inputs */
	CatProximitySensor_Init();

	/* Init Outputs */
	WaterBomb_Init();
	Leds_Init();
	LCD_Init();
	
	/* Init App */
	Controller_Init();
}

void SEOS_Scheduler()
{
	if(++counter_motor == 3)
	{
		FLAG_MOTOR = 1;
	}	
	
}

void SEOS_Dispatcher(void)
/* Lineas del medidor de agua comentadas */
{
	/* Non-Periodic Events Handling */
	if(FLAG_MOTOR){
		WaterBomb_StartPump();
		FLAG_MOTOR = 0;
	}

	/*
	if(FLAG_sense_water_level)
	{
		FLAG_sense_water_level = 0;
		WaterLevelSensor_SenseWaterLevel();
	}
	*/
}

void SEOS_Sleep()
{
}
