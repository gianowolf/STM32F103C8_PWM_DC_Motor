#include "rtc.h"

#include <stm32f103x6.h>

// This function establishes comunication with the RTC
// 0 to write
// 1 to read
void sendAdd(uint8_t);

// This function returns binary coded decimal of the argument
// does not account for larger than 99 numbers
uint8_t toBCD(uint8_t);

// This functions reads data from the RTC argument is address
uint8_t readData(uint8_t);

// This function returns the integer form of the BCD argument
uint8_t toInt(uint8_t);

void i2c_start(void);
void i2c_stop(void);
void i2c_sendData(uint8_t);

void RTC_init() {
	// Enable clocks
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL |= 0xFF000000; // Pins PB6 PB7 as alternate funtion open drain

	I2C1->CR2 = 0x0024; // FREQ = 36
	I2C1->CCR = 0x00B4; // CCR = PB1CLK/2*BAUDRATE = 36 M/ 200 K = 180 = 0xB4 (Standar mode)
	I2C1->TRISE = 37; // TRICE = PB1CLK / 1M + 1

	I2C1->CR1 |= 1; // Enable I2C peripheral
}

void RTC_setTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t month, uint8_t year) {
    sendAdd(0);	

	// Sends the address 0 for seconds
	i2c_sendData(0x00);
	
	i2c_sendData(toBCD(sec));
	i2c_sendData(toBCD(min));
	i2c_sendData(toBCD(hour));
	i2c_sendData(toBCD(0x01)); // We don't care about weekday
	i2c_sendData(toBCD(day));
	i2c_sendData(toBCD(month));
	i2c_sendData(toBCD(year));

	i2c_stop();
}

void sendAdd(uint8_t rw) {
	uint8_t add_sent = 0, arlo = 0;
	uint16_t stat1;
	do {
		while ((I2C1->SR2 & (1<<1)) != 0); // Wait for bus not busy
		i2c_start();
		I2C1->DR = (0x68<<1) + rw; // Sends DS3231 slave address for r/w
		do { // Checks until address is sent or arbitration is lost
			stat1 = I2C1->SR1;
			if ((stat1 & (1<<9)) != 0) {
				arlo = 1;
			} else if ((stat1 & (1<<1)) != 1) {
				add_sent = 1;
			}
		} while (!add_sent & !arlo);
	} while (!add_sent); // Repeats until address is sent
}

uint8_t readData(uint8_t add) {
	sendAdd(0);

	// Sends the address to read
	i2c_sendData(add);
	i2c_stop();

	sendAdd(1);
	I2C1->CR1 |= (1<<10); // Acknowledge enabled
	while ((I2C1->SR1 & (1<<6)) == 0); // Waits for RxNE to set
	return toInt(I2C1->DR);
}

void RTC_getSeconds(uint8_t *sec) {
	*sec = readData(0x00);
}
void RTC_getMinutes(uint8_t *min) {
	*min = readData(0x01);
}
void RTC_getHours(uint8_t *hour) {
	*hour = readData(0x02);
}
void RTC_getDay(uint8_t *day) {
	*day = readData(0x04);
}
void RTC_getMonth(uint8_t *month) {
	*month = readData(0x05);
}
void RTC_getYear(uint8_t *year) {
	*year = readData(0x06);
}

void i2c_start() {
	I2C1->CR1 |= (1<<8); // Generate a start
	while ((I2C1->SR1 & (1<<0)) == 0); // Wait for start generation
}

void i2c_stop() {
	I2C1->CR1 |= (1<<9); // Generate a stop
	while ((I2C1->SR2 & (1<<0)) != 0); // Wait for stop generation
}

void i2c_sendData(uint8_t data) {
	I2C1->DR = data;
	while ((I2C1->SR1 & (1<<7)) != 0); // Waits for TXE to set
}

uint8_t toBCD(uint8_t n) {
	return ((n % 10) | (((n/10) % 10)<<4));
}
uint8_t toInt(uint8_t bcd) {
	return (((bcd>>4) * 10) + (bcd & 0x0F));
}
