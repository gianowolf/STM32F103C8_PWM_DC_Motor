#include "Controller.h"

#include "WaterLevelSensor.h"
#include "buttons.h"
#include "Leds.h"
#include "WaterBomb.h"

typedef enum {
	NORMAL, WORKING_CAT, WORKING, LOW, EMPTY, CLOCK
} states;

static states state; // Curent state of the FSM
static states prev_state;
static uint16_t water_level;
uint8_t timeDate[] = {0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t oneHour(void);

void Controller_Init() {
}

void Controller_Update(){
	switch (state) {
		case NORMAL:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (BUTTON_B()) {
				state = CLOCK;
			} else if (water_level < EMPTY_LEVEL) {
				Leds_WaterLevel_Empty();
				state = EMPTY;
			} else if (water_level < LOW_LEVEL) {
				Leds_WaterLevel_Low();
				state = LOW;
			} else if (CatProximitySensor_SenseProximity()) {
				WaterBomb_StartPump();
				prev_state = NORMAL;
				state = WORKING_CAT;
			} else if (oneHour()) {
				WaterBomb_StartPump();
				prev_state = NORMAL;
				state = WORKING;
			}
			break;
		case WORKING:
			if (timeout) {
				WaterBomb_StopPump();
				state = prev_state;
			} else if (CatProximitySensor_SenseProximity()) {
				state = WORKING_CAT;
			}
			break;
		case WORKING_CAT:
			if (!CatProximitySensor_SenseProximity()) {
				timeout--;
				if (timeout) {
					WaterBomb_StopPump();
					state = prev_state;
				}
			} else if (WaterLevelSensor_GetWaterLevel() < EMPTY_LEVEL) {
				WaterBomb_StopPump();
				Leds_WaterLevel_Empty();
				state = EMPTY;
			}
			break;
		case LOW:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (botón) {
				state = CLOCK;
			} else if (water_level <= EMPTY_LEVEL) {
				Leds_WaterLevel_Empty();
				state = EMPTY;
			} else if (water_level > NOT_LOW_LEVEL) {
				Leds_WaterLevel_Normal();
				state = NORMAL;
			} else if (CatProximitySensor_SenseProximity()) {
				WaterBomb_StartPump();
				prev_state = LOW;
				state = WORKING_CAT;
			} else if (oneHour()) {
				WaterBomb_StartPump();
				prev_state = LOW;
				state = WORKING;
			}
			break;
		case EMPTY:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (botón) {
				state = CLOCK;
			} else if (water_level > NOT_EMPTY_LEVEL) {
				Leds_WaterLevel_Low();
				state = LOW;
			} else if (water_level > NOT_LOW_LEVEL) {
				Leds_WaterLevel_Normal();
				state = NORMAL;
			}
			break;
		case CLOCK:
			if (BUTTON_A()) {
				timeDate[lugar] = timeDate[lugar]++ % 10;
			} else if (BUTTON_B()) {
				if (lugar++ == 12) {
					sec = timeDate[0] * 10 + timeDate[1];
					min = timeDate[2] * 10 + timeDate[3];
					hour = timeDate[4] * 10 + timeDate[5];
					day = timeDate[6] * 10 + timeDate[7];
					month = timeDate[8] * 10 + timeDate[9];
					year = timeDate[10] * 10 + timeDate[11];
					RTC_setTime(sec, min, hour, day, month, year);
				}
			}
			break;
	}
}

uint8_t oneHour() {
	static uint8_t lastH = RTC_getHours();
	uint8_t actualH = RTC_getHours();
	if (lastH != actualH) {
		lastH = actualH;
		return 1;
	} return 0;
}
