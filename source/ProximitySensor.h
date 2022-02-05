#ifndef _CAT_PROXIMITY_SENSOR_H
#define _CAT_PROXIMITY_SENSOR_H

#include <stm32f103x6.h>               
#include <stdint.h>

#include "utils.h"

#define TRIGGER_DISTANCE 35 /* distance [cm] */
#define CALIB 0.00216       /* (error * t) / (clk_freq [MHz] * calib_factor [us/cm] =  (0.9 * t) / (7.2 * 58) = t / 2.16e-03 */

void CatProximitySensor_Init(void);
void CatProximitySensor_SenseProximity(void);
void sendTrigger(void);
#endif
