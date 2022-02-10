#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

void RTC_init(void);
// Function that sets the seconds, minutes, hours, day, month, year
void RTC_setTime(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void RTC_getSeconds(uint8_t*);
void RTC_getMinutes(uint8_t*);
void RTC_getHours(uint8_t*);
void RTC_getDay(uint8_t*);
void RTC_getMonth(uint8_t*);
void RTC_getYear(uint8_t*);

#endif
