/*
 * Ultrasonic_Sensor.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "state.h"

typedef enum{
	ULTRASONIC_BUSY
}US_status_t;

STATE_DEFINE(ULTRASONIC_BUSY);

extern void (*US_State)();

void US_init();
void UlraSonic_Read_Random_Values(int min, int max);

#endif /* ULTRASONIC_SENSOR_H_ */
