/*
 * PressureSensor.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Mohamed Elsayed
 */

#include "PressureSensor.h"


unsigned long seed = 0;
pressureSensorState_t pressureSensorState = PRESSURE_SENSOR_READING;
void (*PS_status)();
static int PS_pressure = 0;

// Function to initialize the seed with the current time
void seedLCG(unsigned long newSeed) {
    seed = newSeed;
}

// Linear Congruential Generator (LCG) implementation
unsigned long lcg() {
    seed = (MULTIPLIER * seed + INCREMENT) % MODULUS;
    return seed;
}

// Function to get a random number in a range [min, max]
int getRandomNumber(int min, int max) {
    return (lcg() % (max - min + 1)) + min;
}

void PressureSensorInit(){
	// initialize the pressure sensor configurations
	//printf("Pressure Sensor has been intialized.\n");
}

int SetPressureValue(){
	// return getRandomNumber(15, 25);
	return getPressureVal();
}

STATE_DEFINE(PressureSensorReading){
	PS_status = STATE(PressureSensorReading);
	pressureSensorState = PRESSURE_SENSOR_READING;
	//printf("\n==== Pressure Sensor Reading State Begin ========\n");
	PS_pressure = SetPressureValue();
	ReadPressureValue(PS_pressure);
	STATE(PressureSensorWaiting)();
	//printf("==== Pressure Sensor Reading State End ========\n");
}

STATE_DEFINE(PressureSensorWaiting){
	// Waits for 10 second on waiting state
	//printf("Waiting for 10 Seconds...\n");
	//Delayms(720000000); // should be 10
}





