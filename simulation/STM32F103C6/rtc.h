#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

void RTC_init(void);
// Function that sets the seconds, minutes, hours, day, month, year
void RTC_setTime(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
uint8_t RTC_getSeconds(void);
uint8_t RTC_getMinutes(void);
uint8_t RTC_getHours(void);
uint8_t RTC_getDay(void);
uint8_t RTC_getMonth(void);
uint8_t RTC_getYear(void);

#endif
