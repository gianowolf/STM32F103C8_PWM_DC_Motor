#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include <stm32f103x6.h> // Device header


//Uncomment this if LCD 4 bit interface is used
#define LCD_4bit

#define LCDPORT_DATA GPIOB
#define LCDIOCLK_DATA RCC_APB2ENR_IOPBEN
#define LCDPORT_CMD GPIOB
#define LCDIOCLK_CMD RCC_APB2ENR_IOPBEN

//Define LCDPIN_XXX_POS to 1 if low pins (0-7) are been used
//Define LCDPIN_XXX_POS to 0 if high pins (8-15) are been used
#define LCDPIN_DATA_POS 1
#define LCDPIN_CMD_POS 0

#define LCD_D0	0	//define MCU pin connected to LCD D0
#define LCD_D1	1	//define MCU pin connected to LCD D1
#define LCD_D2	2	//define MCU pin connected to LCD D1
#define LCD_D3	3	//define MCU pin connected to LCD D2
#define LCD_D4	4	//define MCU pin connected to LCD D3
#define LCD_D5	5	//define MCU pin connected to LCD D4
#define LCD_D6	6	//define MCU pin connected to LCD D5
#define LCD_D7	7	//define MCU pin connected to LCD D6
#define LCD_RS	12	//define MCU pin connected to LCD RS
#define LCD_RW	11	//define MCU pin connected to LCD R/W
#define LCD_E	10	//define MCU pin connected to LCD E

//commands
#define LCD_CLR             0	//DB0: clear display
#define LCD_HOME            1	//DB1: return to home position
#define LCD_ENTRY_MODE      2	//DB2: set entry mode
#define LCD_ENTRY_INC       1	//DB1: increment
#define LCD_ENTRY_SHIFT     0	//DB2: shift
#define LCD_ON_CTRL         3	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2	//DB2: turn display on
#define LCD_ON_CURSOR       1	//DB1: turn cursor on
#define LCD_ON_BLINK        0	//DB0: blinking cursor
#define LCD_MOVE            4	//DB4: move cursor/display
#define LCD_MOVE_DISP       3	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address
// reading:
#define LCD_BUSY            7	//DB7: LCD is busy
#define LCD_LINES						2	//visible lines
#define LCD_LINE_LENGTH		16	//line length (in characters)
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

//Functions
void LCD_init(void); //Initializes LCD
void LCD_sendCommand(uint8_t); //Sends command to LCD
void LCD_sendChar(uint8_t); //Sends character to LCD
void LCD_sendString(uint8_t*, uint8_t); //Sends string to LCD
void LCD_goToXY(uint8_t, uint8_t); //Cursor to X Y position
void LCD_clear(void); //Clears LCD
void LCD_cursorOn(void);		//Underline cursor ON
void LCD_cursorOnBlink(void);	//Underline blinking cursor ON
void LCD_cursorOff(void);		//Cursor OFF
void LCD_visible(void);			//LCD visible

#endif
