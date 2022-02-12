#include "lcd.h"

void delay_us(uint16_t);
void load_data(uint8_t);

void LCD_sendCommand(uint8_t cmd){
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW);
	load_data(cmd);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	if (cmd <= 3)
		delay_us(2000);
	else
		delay_us(50);
}

void LCD_sendChar(uint8_t ch) {
	LCDPORT_CMD->BSRR = (1<<LCD_RS | 1<<(LCD_RW + 16));
	load_data(ch);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(50);
	LCDPORT_CMD->BRR = (1<<LCD_RS);
}

void LCD_init(){
	// Made as per the HD44780 datasheet
	delay_us(50000); // Wait more than 40 ms
	
	RCC->APB2ENR |= LCDIOCLK_CMD | LCDIOCLK_DATA; // Starts clock for LCD port/s
	
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW | 1<<LCD_E); // Pins to 0
	// Sets pins as outputs
#if LCDPIN_CMD_POS 
	LCDPORT_CMD->CRL = ((LCDPORT_CMD->CRL & ~(12<<LCD_RS*4 | 12<<LCD_RW*4 | 12<<LCD_E*4)) | (3<<LCD_RS*4 | 3<<LCD_RW*4 | 3<<LCD_E*4));
#else
	LCDPORT_CMD->CRH = ((LCDPORT_CMD->CRH & ~(12<<(LCD_RS-8)*4 | 12<<(LCD_RW-8)*4 | 12<<(LCD_E-8)*4)) | (3<<(LCD_RS-8)*4 | 3<<(LCD_RW-8)*4 | 3<<(LCD_E-8)*4));
#endif
	
	LCDPORT_DATA->BRR = (1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D5 | 1<<LCD_D4); // Pins to 0
	// Sets pins as outputs
#if LCDPIN_DATA_POS
	LCDPORT_DATA->CRL = ((LCDPORT_DATA->CRL 
		& ~(12<<LCD_D4*4 | 12<<LCD_D5*4 | 12<<LCD_D6*4 | 12<<LCD_D7*4)) 
		| (3<<LCD_D4*4 | 3<<LCD_D5*4 | 3<<LCD_D6*4 | 3<<LCD_D7*4));
#else
	LCDPORT_DATA->CRH = ((LCDPORT_DATA->CRH 
		& ~(12<<(LCD_D4-8)*4 | 12<<(LCD_D5-8)*4 | 12<<(LCD_D6-8)*4 | 12<<(LCD_D7-8)*4)) 
		| (3<<(LCD_D4-8)*4 | 3<<(LCD_D5-8)*4 | 3<<(LCD_D6-8)*4 | 3<<(LCD_D7-8)*4));
#endif
	//-----One---------
	LCDPORT_DATA->BSRR = (1<<LCD_D5 | 1<<LCD_D4 | 1<<(LCD_D7 + 16) | 1<<(LCD_D6 + 16));
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(4500); // Wait more than 4.2 ms
	
	//-----Two---------
	LCDPORT_DATA->BSRR = (1<<LCD_D5 | 1<<LCD_D4 | 1<<(LCD_D7 + 16) | 1<<(LCD_D6 + 16));
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(150); // Wait more than 100 us
	
	//-----Three-------
	LCDPORT_DATA->BSRR = (1<<LCD_D5 | 1<<LCD_D4 | 1<<(LCD_D7 + 16) | 1<<(LCD_D6 + 16));
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(50);
#ifdef LCD_4bit // 4-bit part
	LCDPORT_DATA->BSRR = (1<<LCD_D5 | 1<<(LCD_D4 + 16) | 1<<(LCD_D7 + 16) | 1<<(LCD_D6 + 16));
	LCDPORT_CMD->BRR = (1<<LCD_RS | 1<<LCD_RW);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(1);
	// Set interface 4-bit 2 line display
	LCD_sendCommand(0x28);
#else // 8-bit part
	LCDPORT_DATA->BRR = (1<<LCD_D3 | 1<<LCD_D2 | 1<<LCD_D1 | 1<<LCD_D0); // Pins to 0
	// Sets pins as outputs
	#if LCDPIN_DATA_POS
		LCDPORT_DATA->CRL = ((LCDPORT_DATA->CRL 
			& ~(12<<LCD_D0*4 | 12<<LCD_D1*4 | 12<<LCD_D2*4 | 12<<LCD_D3*4)) 
			| (3<<LCD_D0*4 | 3<<LCD_D1*4 | 3<<LCD_D2*4 | 3<<LCD_D3*4));
	#else
		LCDPORT_DATA->CRH = ((LCDPORT_DATA->CRH 
			& ~(12<<(LCD_D0-8)*4 | 12<<(LCD_D1-8)*4 | 12<<(LCD_D2-8)*4 | 12<<(LCD_D3-8)*4)) 
			| (3<<(LCD_D0-8)*4 | 3<<(LCD_D1-8)*4 | 3<<(LCD_D2-8)*4 | 3<<(LCD_D3-8)*4));
	#endif
	// Set interface 8-bit 2 line display
	LCD_sendCommand(0x38);
#endif
	// Visible display - increment address - cursor off
	LCD_sendCommand(0x0C);
}

void LCD_sendString(uint8_t* st, uint8_t l){
	uint8_t i ;
	for (i= 0; i < l; i++) {
		LCD_sendChar(st[i]);
	}
}

void LCD_goToXY(uint8_t x, uint8_t y){ //Cursor to X Y position
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y){
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCD_sendCommand(1<<LCD_DDRAM | DDRAMAddr);	
}

void LCD_clear(void) { //Clears LCD
	LCD_sendCommand(1<<LCD_CLR);
}

void LCD_cursorOn(void){ //displays LCD cursor
	LCD_sendCommand(0x0E);
}

void LCD_cursorOnBlink(void){ //displays LCD blinking cursor
	LCD_sendCommand(0x0F);
}

void LCD_cursorOFF(void){ //turns OFF cursor
	LCD_sendCommand(0x0C);
}

void LCD_visible(void){ //Shows LCD
	LCD_sendCommand(0x0C);
}

void load_data(uint8_t data) {
#ifdef LCD_4bit // 4-bit part
	// High
	LCDPORT_DATA->BSRR = (1<<((data & (1<<7))? LCD_D7 : (LCD_D7 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<6))? LCD_D6 : (LCD_D6 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<5))? LCD_D5 : (LCD_D5 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<4))? LCD_D4 : (LCD_D4 + 16)));
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_us(1);

	//Low
	LCDPORT_DATA->BSRR = (1<<((data & (1<<3))? LCD_D7 : (LCD_D7 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<2))? LCD_D6 : (LCD_D6 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<1))? LCD_D5 : (LCD_D5 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<0))? LCD_D4 : (LCD_D4 + 16)));
#else // 8-bit part
	LCDPORT_DATA->BSRR = (1<<((data & (1<<7))? LCD_D7 : (LCD_D7 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<6))? LCD_D6 : (LCD_D6 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<5))? LCD_D5 : (LCD_D5 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<4))? LCD_D4 : (LCD_D4 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<3))? LCD_D3 : (LCD_D3 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<2))? LCD_D2 : (LCD_D2 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<1))? LCD_D1 : (LCD_D1 + 16)));
	LCDPORT_DATA->BSRR = (1<<((data & (1<<0))? LCD_D0 : (LCD_D0 + 16)));
#endif
}

void delay_us(uint16_t t){ // Dalay works for CPU_freq = 72MHz
	uint16_t l, i;
	for(i = 0; i < t; i++)
		for(l = 0; l < 12; l++){}
}
