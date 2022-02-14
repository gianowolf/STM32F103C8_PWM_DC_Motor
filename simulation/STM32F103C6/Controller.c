#include "Controller.h"

#include "WaterLevelSensor.h"
#include "buttons.h"
#include "Leds.h"
#include "WaterBomb.h"
#include "LCD.h"
#include "rtc.h"
#include "CatProximitySensor();

typedef enum {
	NORMAL, WORKING_CAT, WORKING, LOW, EMPTY, CLOCK
} states;

static states state; // Curent state of the FSM
static states prev_state;
static uint16_t prev_level;
static uint16_t water_level;
static uint8_t timeDate[] = {0,0,0,0,0,0,0,0,0,0,0,0};
static uint8_t place = 0;
static uint32_t drinkedWater = 0;
uint8_t sec, min, hour, day, month, year;

void writeTimeDate(void);
void writeDrinkedWater(void);
uint8_t oneHour(void);
uint8_t newDay(void);
void loadTime(void)

void Controller_Init() {
	RTC_init();
	LCD_init();
	WaterBomb_Init();
	WaterLevelSensor_Init();
	CatProximitySensor_Init();
	Leds_Init();
	BUTTONS_init();
	loadTime();
	LCD_cursorOff();
	writeDrinkedWater();
	state = NORMAL;
}

void Controller_Update(){
	if (newDay()) {
		drinkedWater = 0;
	}
	switch (state) {
		case NORMAL:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (BUTTON_B()) {
				place = 0;
				writeTimeDate();
				prev_state = NORMAL;
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
				prev_level = water_level;
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
				prev_level = water_level;
				state = WORKING_CAT;
			}
			break;
		case WORKING_CAT:
			if (!CatProximitySensor_SenseProximity()) {
				timeout--;
				if (timeout) {
					water_level = WaterLevelSensor_GetWaterLevel();
					if (water_level < prev_level) {
						drinkedWater += (prev_level - water_level);
					}
					WaterBomb_StopPump();
					LCD_writeDrinkedWater();
					state = prev_state;
				}
			} else if (WaterLevelSensor_GetWaterLevel() < EMPTY_LEVEL) {
				WaterBomb_StopPump();
				LCD_writeDrinkedWater();
				Leds_WaterLevel_Empty();
				state = EMPTY;
			}
			break;
		case LOW:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (BUTTON_B()) {
				place = 0;
				writeTimeDate();
				prev_state = LOW;
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
				prev_level = water_level;
				state = WORKING_CAT;
			} else if (oneHour()) {
				WaterBomb_StartPump();
				prev_state = LOW;
				state = WORKING;
			}
			break;
		case EMPTY:
			water_level = WaterLevelSensor_GetWaterLevel();
			if (BUTTON_B()) {
				place = 0;
				writeTimeDate();
				prev_state = EMPTY;
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
				timeDate[place] = (timeDate[place] + 1) % 10;
				LCD_sendChar(timeDate[place] + '0');
			} else if (BUTTON_B()) {
				if (lugar++ == 12) {
					sec = timeDate[0] * 10 + timeDate[1];
					min = timeDate[2] * 10 + timeDate[3];
					hour = timeDate[4] * 10 + timeDate[5];
					day = timeDate[6] * 10 + timeDate[7];
					month = timeDate[8] * 10 + timeDate[9];
					year = timeDate[10] * 10 + timeDate[11];
					RTC_setTime(sec, min, hour, day, month, year);
					LCD_cursorOff();
					LCD_writeDrinkedWater();
					state = prev_state;
				}
			}
			switch (place) {
				case 0: LCD_goToXY(6,0); break;
				case 1: LCD_goToXY(7,0); break;
				case 2: LCD_goToXY(9,0); break;
				case 3: LCD_goToXY(10,0); break;
				case 4: LCD_goToXY(12,0); break;
				case 5: LCD_goToXY(13,0); break;
				case 6: LCD_goToXY(7,1); break;
				case 7: LCD_goToXY(8,1); break;
				case 8: LCD_goToXY(10,1); break;
				case 9: LCD_goToXY(11,1); break;
				case 10: LCD_goToXY(13,1); break;
				case 11: LCD_goToXY(14,1); break;
			}
			break;
	}
}

void writeTimeDate() {
	LCD_clear();
	LCD_goToXY(0,0);
	LCD_sendString((uint8_t*)"Hora: ", 6);
	LCD_sendChar(timeDate[0] + '0');
	LCD_sendChar(timeDate[1] + '0');
	LCD_sendChar(':');
	LCD_sendChar(timeDate[2] + '0');
	LCD_sendChar(timeDate[3] + '0');
	LCD_sendChar(':');
	LCD_sendChar(timeDate[4] + '0');
	LCD_sendChar(timeDate[5] + '0');
	LCD_goToXY(0,1);
	LCD_sendString((uint8_t*)"Fecha: ", 7);
	LCD_sendChar(timeDate[6] + '0');
	LCD_sendChar(timeDate[7] + '0');
	LCD_sendChar('/');
	LCD_sendChar(timeDate[8] + '0');
	LCD_sendChar(timeDate[9] + '0');
	LCD_sendChar('/');
	LCD_sendChar(timeDate[10] + '0');
	LCD_sendChar(timeDate[11] + '0');
	LCD_goToXY(6,0);
	LCD_cursorOnBlink();
}

void writeDrinkedWater() {
	uint16_t auxDW = drinkedWater;
	LCD_clear();
	LCD_goToXY(0,0);
	LCD_sendString((uint8_t*)"Agua bebida hoy:", 16);
	LCD_goToXY(3,1);
	LCD_sendChar((auxDW % 10) + '0');
	auxDW /= 10;
	LCD_goToXY(2,1);
	LCD_sendChar((auxDW % 10) + '0');
	auxDW /= 10;
	LCD_goToXY(1,1);
	LCD_sendChar((auxDW % 10) + '0');
	auxDW /= 10;
	LCD_goToXY(0,1);
	LCD_sendChar((auxDW % 10) + '0');
	LCD_goToXY(4,1);
	LCD_sendString((uint8_t*)" mL", 3);
}

void loadTime() {
	uint8_t aux;
	aux = RTC_getSeconds();
	timeDate[0] = aux / 10;
	timeDate[1] = aux % 10;
	aux = RTC_getMinutes();
	timeDate[2] = aux / 10;
	timeDate[3] = aux % 10;
	aux = RTC_getHours();
	timeDate[4] = aux / 10;
	timeDate[5] = aux % 10;
	aux = RTC_getDay();
	timeDate[6] = aux / 10;
	timeDate[7] = aux % 10;
	aux = RTC_getMonth();
	timeDate[8] = aux / 10;
	timeDate[9] = aux % 10;
	aux = RTC_getYear();
	timeDate[10] = aux / 10;
	timeDate[11] = aux % 10;
}

uint8_t oneHour() {
	static uint8_t lastH = RTC_getHours();
	uint8_t actualH = RTC_getHours();
	if (lastH != actualH) {
		lastH = actualH;
		return 1;
	} return 0;
}

uint8_t oneHour() {
	static uint8_t today = RTC_getDay();
	uint8_t day = RTC_getDay();
	if (today != day) {
		today = day;
		return 1;
	} return 0;
}
