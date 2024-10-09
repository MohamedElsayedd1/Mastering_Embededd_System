/*
 * main.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Mohamed Elsayed
 */

#include "PressureSensor.h"
#include "AlarmMonitor.h"

static int pressure;
static const int threshold = 20;

void setup(){
	// Intialize GPIO
	GPIO_INITIALIZATION ();

	// Initialize Modules
	PressureSensorInit();
	AlarmMonitorInit();

	// Set the function pointers
	PS_status = STATE(PressureSensorReading);
	alarmState = STATE(AlarmOff);
}

int main(){
	// Configure and initialize the system
	setup();

	while(1){
		alarmState();
		PS_status();
		CheckPressureValue();
		
	}

	return 0;
}


void ReadPressureValue(int p){
	pressure = p;
	//printf("Pressure Sensor -----------------> Main (Pressure = %d)\n", pressure);
}

void CheckPressureValue(){
	//printf("\nMain -----------------> Alarm Monitor (Pressure = %d)\n", pressure);
	if(pressure >= threshold){
		HighPressureDetected(); // Send High pressure detection to Alarm Monitor Module
	}
}
