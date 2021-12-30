#include "seos.h"
#include "lrc.h"
#include "rc.h"
#include "lcd.h"

/* PUBLIC FLAGS */
static volatile uint32_t Flag_measure;
static volatile uint32_t Flag_print;

/* PRIVATE */
int seos_init(void);

static volatile uint8_t counter_measure;
static volatile uint8_t counter_print;

void SysTick_Handler(void) {
	SEOS_Schedule();
}

int seos_init(void)
{
	Flag_measure  = 0;
	Flag_print = 0;
	//se inicializan los flags y contadores
	counter_measure = 4;
	counter_print = 0;
	
	//se configura el sistem tick para interrupir una vez cada 100 ms
	if (SysTick_Config(SystemCoreClock / 10)){
		//error handling
	}

	return 0;
}

int SEOS_Boot(void) {
	//inicializa todos los módulos
	LCD_init();
	RC_init();
	LRC_init();
	seos_init();
	return 0;
}

int SEOS_Schedule(void)
{
	//el planificador levanta el flag de las tareas que se tengan que despachar
	if(++counter_measure == OVERF_MEASURE)
	{
		Flag_measure   = 1; 
		counter_measure = 0;
	}
	if(++counter_print == OVERF_PRINT)
	{
		Flag_print  = 1; 
		counter_print= 0;
	}
	return 0;
}

int SEOS_Dispatch(void)
{
	//el despachador ejecuta las tareas que estén pendientes y baja los flags
	if(Flag_measure) {
		LRC_measure();
		RC_measure();
		Flag_measure = 0;
	}
	if(Flag_print){
		LRC_print();
		RC_Print();
		Flag_print = 0;
	}
	return 0;
}

int SEOS_Sleep(void)
{
	//sleep no se implementa en la simulación
	return 0;
}
