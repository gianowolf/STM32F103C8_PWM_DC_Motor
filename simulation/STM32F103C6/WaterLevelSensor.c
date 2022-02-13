#include "WaterLevelSensor.h"

#define PI 3.141592654

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
	volatile uint32_t height;
	ADC1->CR2 |= 1; // Starts a conversion
	while((ADC1->SR & (1<<1)) == 0){} // Waits for conversion to finish
	height = ADC1->DR; // Read the converted data and resets SR EOC
	if (height < 3125) {
		return 0;
	}
	height = (height - 3125) * 64; // Height value in micrometers
#ifdef CUBOID_TANK // Cuboid tank part
	height *= (TANK_WIDTH * TANK_LENGTH);
#else // Cylindrical tank part
	height = (TANK_RADIUS * TANK_RADIUS * height * PI );
#endif
	return height/10000; // Returns the calculated volume in cm3
}
