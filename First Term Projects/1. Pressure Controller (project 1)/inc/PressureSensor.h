/*
 * PressureSensor.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

#include "state.h"
#include "GPIO.h"

// Define constants for the LCG
#define MODULUS 2147483648  // 2^31
#define MULTIPLIER 1103515245
#define INCREMENT 12345

typedef enum{
	PRESSURE_SENSOR_READING,
	PRESSURE_SENSOR_WAITING
}pressureSensorState_t;

extern pressureSensorState_t pressureSensorState;
extern void (*PS_status)();

void PressureSensorInit();
int SetPressureValue();
STATE_DEFINE(PressureSensorReading);
STATE_DEFINE(PressureSensorWaiting);

#endif /* PRESSURESENSOR_H_ */
