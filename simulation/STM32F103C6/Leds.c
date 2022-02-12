#include "Leds.h"

void Leds_Init(void) {
	LED_G_pin > 7 ? LED_G_port->CRH = (LED_G_port->CRH | (3<<((LED_G_pin - 8)*4))) & (0xFFFFFFFF & (3<<((LED_G_pin - 8)*4))) 
					: LED_G_port->CRL = (LED_G_port->CRL | (3<<(LED_G_pin*4))) & (0xFFFFFFFF & (3<<(LED_G_pin*4)));
	LED_Y_pin > 7 ? LED_Y_port->CRH = (LED_Y_port->CRH | (3<<((LED_Y_pin - 8)*4))) & (0xFFFFFFFF & (3<<((LED_Y_pin - 8)*4))) 
					: LED_Y_port->CRL = (LED_Y_port->CRL | (3<<(LED_Y_pin*4))) & (0xFFFFFFFF & (3<<(LED_Y_pin*4)));
	LED_R_pin > 7 ? LED_R_port->CRH = (LED_R_port->CRH | (3<<((LED_R_pin - 8)*4))) & (0xFFFFFFFF & (3<<((LED_R_pin - 8)*4))) 
					: LED_R_port->CRL = (LED_R_port->CRL | (3<<(LED_R_pin*4))) & (0xFFFFFFFF & (3<<(LED_R_pin*4)));
	LED_G_port->BRR = (1<<LED_G_pin);
	LED_Y_port->BRR = (1<<LED_Y_pin);
	LED_R_port->BRR = (1<<LED_R_pin);
	// Sets led pins as outputs
}

void Leds_WaterLevel_Normal(void) { // Turns off red and yellow, turns on green
	LED_R_port->BRR = (1<<LED_R_pin);
	LED_Y_port->BRR = (1<<LED_Y_pin);
	LED_G_port->BSRR = (1<<LED_G_pin);
}

void Leds_WaterLevel_Low(void) { // Turns off red and green, turns on yellow
	LED_R_port->BRR = (1<<LED_R_pin);
	LED_G_port->BRR = (1<<LED_G_pin);
	LED_Y_port->BSRR = (1<<LED_Y_pin);
}

void Leds_WaterLevel_Empty(void) { // Turns off green and yellow, turns on red
	LED_G_port->BRR = (1<<LED_G_pin);
	LED_Y_port->BRR = (1<<LED_Y_pin);
	LED_R_port->BSRR = (1<<LED_R_pin);
}
