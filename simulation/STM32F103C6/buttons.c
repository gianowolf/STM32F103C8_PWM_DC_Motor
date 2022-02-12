#include "buttons.h"

void BUTTONS_init() {
	BUTTON_A_pin > 7 ? BUTTON_A_port->CRH = BUTTON_A_port->CRH | (4<<BUTTON_A_pin
}
