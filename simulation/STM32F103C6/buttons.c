#include "buttons.h"

void BUTTONS_init() {
	RCC->APB2ENR |= BUTTON_A_clock | BUTTON_B_clock;
	if (BUTTON_A_pin > 7) {
		BUTTON_A_port->CRH = ((BUTTON_A_port->CRH | (3<<((BUTTON_A_pin - 8)*4))) & (0xFFFFFFFF & ~(12<<((BUTTON_A_pin - 8)*4))));
	} else {
		BUTTON_A_port->CRL = ((BUTTON_A_port->CRL | (3<<(BUTTON_A_pin * 4))) & (0xFFFFFFFF & ~(12<<(BUTTON_A_pin * 4))));
	}
	if (BUTTON_B_pin > 7) {
		BUTTON_B_port->CRH = ((BUTTON_B_port->CRH | (3<<((BUTTON_B_pin - 8)*4))) & (0xFFFFFFFF & ~(12<<((BUTTON_B_pin - 8)*4))));
	} else {
		BUTTON_B_port->CRL = ((BUTTON_B_port->CRL | (3<<(BUTTON_B_pin * 4))) & (0xFFFFFFFF & ~(12<<(BUTTON_B_pin * 4))));
	}
	BUTTON_A_port->BSRR = (1<<BUTTON_A_pin);
	BUTTON_B_port->BSRR = (1<<BUTTON_B_pin);
	// Sets button pins as inputs with pull-up
}

uint8_t BUTTON_A() {
	volatile uint16_t key;
	static uint16_t old_key = 0xFF, multiple = 4; 

	key = BUTTON_A_port->IDR & (1<<BUTTON_A_pin);

	if (key != 0) {
		multiple = 4;
		old_key = 0xFF;
		return 0;
	} else if (key==old_key) { // 2nd debouncing
		if (multiple++ == 4) {
			// Allows multiple dettections when keeping the key pressed but only once every 4 calls
			multiple = 0;
			return 1;
		}
	}
	old_key = key; // 1st debouncing 
	return 0;
}

uint8_t BUTTON_B() {
	volatile uint16_t key;
	static uint16_t old_key = 2, multiple = 4; 

	key = BUTTON_B_port->IDR & (1<<BUTTON_B_pin);

	if (key != 0) {
		multiple = 4;
		old_key = 2;
		return 0;
	} else if (key==old_key) { // 2nd debouncing
		if (multiple++ == 4) {
			// Allows multiple dettections when keeping the key pressed but only once every 4 calls
			multiple = 0;
			return 1;
		}
	}
	old_key = key; // 1st debouncing 
	return 0;
}
