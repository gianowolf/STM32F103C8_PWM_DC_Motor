#include "Seos.h"

#include <stdint.h>

#include "Controller.h"

static volatile uint32_t flag_update, counter_update;

void seos_init(void);


void SysTick_Handler(void) {
	SEOS_Scheduler();
}

void seos_init(void) {
	counter_update = 0;
	flag_update = 0;
	
	if(SysTick_Config(SystemCoreClock/100)) // System tick every 100 ms
	{ /* Error handling */ }
}

void SEOS_Boot() {
	seos_init();

	// Init App
	Controller_Init();
}

void SEOS_Scheduler() {
	if (counter_update++ == OVERF_UPDATE) {
		counter_update = 0;
		flag_update = 1;
	}
}

void SEOS_Dispatcher(void) {
	if (flag_update) {
		Controller_Update();
		flag_update = 0;
	}
}

void SEOS_Sleep() {
	// sleep()
}
