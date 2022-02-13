#include "lcd.h"
#include <stdint.h>

void delay_ms(uint16_t);
void delay_us(uint16_t);

void LCD_init(void){
	delay_ms(15); //Wait 15 ms after power on for initialization
	
	RCC->APB2ENR |= LCDIOCLK_CMD | LCDIOCLK_DATA; //Starts clock for LCD port/s
	LCDPORT_CMD->ODR &= ~(1<<LCD_RS | 1<<LCD_RW | 1<<LCD_E); //Pins to 0

#if LCDPIN_CMD_POS
	LCDPORT_CMD->CRL = ((LCDPORT_CMD->CRL & ~(12<<LCD_RS*4 | 12<<LCD_RW*4 | 12<<LCD_E*4)) | (3<<LCD_RS*4 | 3<<LCD_RW*4 | 3<<LCD_E*4));
#else
	LCDPORT_CMD->CRH = ((LCDPORT_CMD->CRH & ~(12<<(LCD_RS-8)*4 | 12<<(LCD_RW-8)*4 | 12<<(LCD_E-8)*4)) | (3<<(LCD_RS-8)*4 | 3<<(LCD_RW-8)*4 | 3<<(LCD_E-8)*4));
#endif
	
#ifdef LCD_4bit	//4 bit part
	LCDPORT_DATA->ODR &= ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D5 | 1<<LCD_D4);
	#if LCDPIN_DATA_POS
		LCDPORT_DATA->CRL = ((LCDPORT_DATA->CRL 
			& ~(12<<LCD_D4*4 | 12<<LCD_D5*4 | 12<<LCD_D6*4 | 12<<LCD_D7*4)) 
			| (3<<LCD_D4*4 | 3<<LCD_D5*4 | 3<<LCD_D6*4 | 3<<LCD_D7*4));
	#else
		LCDPORT_DATA->CRH = ((LCDPORT_DATA->CRH 
			& ~(12<<(LCD_D4-8)*4 | 12<<(LCD_D5-8)*4 | 12<<(LCD_D6-8)*4 | 12<<(LCD_D7-8)*4)) 
			| (3<<(LCD_D4-8)*4 | 3<<(LCD_D5-8)*4 | 3<<(LCD_D6-8)*4 | 3<<(LCD_D7-8)*4));
	#endif
   //---------one------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR & ~(1<<LCD_D7 | 1<<LCD_D6)) | (1<<LCD_D5 | 1<<LCD_D4));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//-----------two-----------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR & ~(1<<LCD_D7 | 1<<LCD_D6)) | (1<<LCD_D5 | 1<<LCD_D4));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//-------three-------------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR & ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D4)) | (1<<LCD_D5));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//--------4 bit--dual line---------------
	LCD_sendCommand(0x28);
   //-----increment address, invisible cursor shift------
	LCD_sendCommand(0x0C);
#else //8 bit part
	LCDPORT_DATA->ODR &= ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D5 | 1<<LCD_D4 | 1<<LCD_D3 | 1<<LCD_D2 | 1<<LCD_D1 | 1<<LCD_D0);
	#if LCDPIN_DATA_POS
		LCDPORT_DATA->CRL = ((LCDPORT_DATA->CRL 
			& ~(12<<LCD_D0*4 | 12<<LCD_D1*4 | 12<<LCD_D2*4 | 12<<LCD_D3*4 | 12<<LCD_D4*4 | 12<<LCD_D5*4 | 12<<LCD_D6*4 | 12<<LCD_D7*4)) 
			| (3<<LCD_D0*4 | 3<<LCD_D1*4 | 3<<LCD_D2*4 | 3<<LCD_D3*4 | 3<<LCD_D4*4 | 3<<LCD_D5*4 | 3<<LCD_D6*4 | 3<<LCD_D7*4));
	#else
		LCDPORT_DATA->CRH = ((LCDPORT_DATA->CRH 
			& ~(12<<(LCD_D0-8)*4 | 12<<(LCD_D1-8)*4 | 12<<(LCD_D2-8)*4 | 12<<(LCD_D3-8)*4 | 12<<(LCD_D4-8)*4 | 12<<(LCD_D5-8)*4 | 12<<(LCD_D6-8)*4 | 12<<(LCD_D7-8)*4)) 
			| (3<<(LCD_D0-8)*4 | 3<<(LCD_D1-8)*4 | 3<<(LCD_D2-8)*4 | 3<<(LCD_D3-8)*4 | 3<<(LCD_D4-8)*4 | 3<<(LCD_D5-8)*4 | 3<<(LCD_D6-8)*4 | 3<<(LCD_D7-8)*4);
	#endif
   //---------one------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR 
		& ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D3 | 1<<LCD_D2 | 1<<LCD_D1 | 1<<LCD_D0)) 
		| (1<<LCD_D5 | 1<<LCD_D4));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//-----------two-----------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR 
		& ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D3 | 1<<LCD_D2 | 1<<LCD_D1 | 1<<LCD_D0)) 
		| (1<<LCD_D5 | 1<<LCD_D4));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//-------three-------------
	LCDPORT_DATA->ODR = ((LCDPORT_DATA->ODR 
		& ~(1<<LCD_D7 | 1<<LCD_D6 | 1<<LCD_D3 | 1<<LCD_D2 | 1<<LCD_D1 | 1<<LCD_D0)) 
		| (1<<LCD_D5 | 1<<LCD_D4));
	LCDPORT_CMD->ODR = ((LCDPORT_CMD->ODR & ~(1<<LCD_RS | 1<<LCD_RW)) | (1<<LCD_E));
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
	//--------8 bit dual line----------
	LCD_sendCommand(0x38);
  //-----increment address, invisible cursor shift------
	LCD_sendCommand(0x0C);
#endif
}

void LCD_sendChar(uint8_t ch) { //Sends Char to LCD
#ifdef LCD_4bit //4 bit part
	// High
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<7))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<6))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<5))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<4))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_CMD->BSRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(40);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	delay_us(40);
	
	//Low
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<3))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<2))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<1))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<0))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_CMD->BSRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_us(40);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	delay_us(40);
#else //8 bit part
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<7))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<6))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<5))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<4))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<3))? LCD_D3 : (LCD_D3 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<2))? LCD_D2 : (LCD_D2 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<1))? LCD_D1 : (LCD_D1 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((ch & (1<<0))? LCD_D0 : (LCD_D0 + 16) % 32));
	LCDPORT_CMD->BSRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	delay_ms(1);
#endif
}

void LCD_sendCommand(uint8_t cmd) { //Sends Command to LCD
#ifdef LCD_4bit	 //4 bit part
	// High
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<7))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<6))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<5))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<4))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);

	//Low
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<3))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<2))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<1))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<0))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
#else //8 bit part
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<7))? LCD_D7 : (LCD_D7 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<6))? LCD_D6 : (LCD_D6 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<5))? LCD_D5 : (LCD_D5 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<4))? LCD_D4 : (LCD_D4 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<3))? LCD_D3 : (LCD_D3 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<2))? LCD_D2 : (LCD_D2 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<1))? LCD_D1 : (LCD_D1 + 16) % 32));
	LCDPORT_DATA->BSRR = (1<<((cmd & (1<<0))? LCD_D0 : (LCD_D0 + 16) % 32));
	LCDPORT_CMD->BRR = (1<<LCD_RS);
	LCDPORT_CMD->BSRR = (1<<LCD_E);
	delay_ms(1);
	LCDPORT_CMD->BRR = (1<<LCD_E);
	delay_ms(1);
#endif
}

//delays
void delay_ms(uint16_t t){
	uint16_t i;
	for(i = 0; i < t; i++)
		delay_us(1000);
}

void delay_us(uint16_t t){
	uint16_t l, i;
	for(i = 0; i < t; i++)
		for(l = 0; l < 12; l++){}
}

void LCD_clear(void) { //Clears LCD
	LCD_sendCommand(1<<LCD_CLR);
}

void LCD_sendString(uint8_t* data, uint8_t nBytes){//Outputs string to LCD
	register uint8_t i;
	// check to make sure we have a good pointer
	if (!data) return;
	// print data
	for(i=0; i<nBytes; i++){
		LCD_sendChar(data[i]);
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
