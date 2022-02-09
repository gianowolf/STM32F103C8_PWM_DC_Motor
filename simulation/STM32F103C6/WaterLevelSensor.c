#include "WaterLevelSensor.h"

#include "utils.h"

void WaterLevelSensor_Init() {
	// Enable clocks
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	
	// Configures adc_pin1 as analog input;
	GPIOA->CRL &= 0xFFFFFF0F;
	
	// Turn on ADC - Right alignment - Single conversion
	ADC1->CR2 = 1;
	
	// Sets sample time to 7.5 ADC clock cycles 
	ADC1->SMPR2 = 1<<3;
	
	Utils_Delay_us(1);
	
	// Sets channel 1 as the input
	ADC1->SQR3 = 1;
}

uint16_t WaterLevelSensor_GetWaterLevel() {
	ADC1->CR2 |= 1; // Starts a conversion
	while((ADC1->SR & (1<<1)) == 0){} // Waits for conversion to finish
	return (uint16_t) ADC1->DR; // Returns the converted data and resets SR EOC
}
