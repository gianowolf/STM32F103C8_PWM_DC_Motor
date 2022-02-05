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
#ifndef _SEOS_H
#define _SEOS_H

#include <stm32f103x6.h>
#include <inttypes.h>
#include <stdio.h>

/* Overflow */
/* nro de tick del sistema en el que se debe ejecutar la tarea y reiniciar el contador */
#define INIT_MEASURE 3
#define INIT_PRINT 0 
#define OVERF_MEASURE 5 // 0.5 s 
#define OVERF_PRINT 5 // 0.5 s

/* Public Functions */
int SEOS_Boot(void);

int SEOS_Schedule(void);

int SEOS_Dispatch(void);

int SEOS_Sleep(void);

#endif
