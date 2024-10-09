/*
 * AlarmMonitor.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Mohamed Elsayed
 */
#include "AlarmMonitor.h"

alarmMonitorStatus_t alarmMonitorStatus;
void(*alarmState)();

void AlarmMonitorInit(){
	// initialize the Alarm Monitor configurations
	//printf("Alarm Monitor has been intialized.\n");
}

void HighPressureDetected(){
	alarmState = STATE(AlarmOn);
}

STATE_DEFINE(AlarmOff){
	alarmMonitorStatus = ALARM_MONITOR_OFF;
	alarmState = STATE(AlarmOff);
	//printf("\n==== Alarm Monitor OFF State Begin ========\n");
	Set_Alarm_actuator(1); // Turn off Led Alarm
	//printf("Alarm is OFF.\n");
	//printf("==== Alarm Monitor OFF State End ========\n");
}

STATE_DEFINE(AlarmOn){
	alarmMonitorStatus = ALARM_MONITOR_ON;
	alarmState = STATE(AlarmOn);
	//printf("\n==== Alarm Monitor ON State Begin ========\n");
	Set_Alarm_actuator(0); // Turn On Led Alarm
	//printf("Alarm is ON.\n");
	//printf("==== Alarm Monitor ON State End ========\n");
	Delayms(6000); // Delay for ~6 seconds
	//printf("\nDelay for 6 seconds.\n");
	alarmState = STATE(AlarmOff);
	alarmState();
}
