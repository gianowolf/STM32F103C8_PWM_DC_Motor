#ifndef _SEOS_H
#define _SEOS_H

/* MCU Device Header */
#include <stm32f103x6.h>

#define OVERF_UPDATE 2

void SEOS_Boot(void);
void SEOS_Scheduler(void);
void SEOS_Dispatcher(void);
void SEOS_Sleep(void);

#endif
