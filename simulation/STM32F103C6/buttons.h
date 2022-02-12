#indef BUTTONS_H_
#define BUTTONS_H_

#include <stm32f103x6.h>
#include <stdint.h>

#define BUTTON_A_port GPIOB
#define BUTTON_A_pin 8
#define BUTTON_B_port GPIOB
#define BUTTON_B_pin 9

void BUTTONS_init(void);
uint8_t BUTTON_A(void);
uint8_t BUTTON_B(void);

#endif
