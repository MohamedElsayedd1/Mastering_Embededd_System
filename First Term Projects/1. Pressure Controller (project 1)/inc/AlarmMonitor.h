/*
 * AlarmMonitor.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_

#include "state.h"
#include "GPIO.h"

typedef enum{
	ALARM_MONITOR_OFF,
	ALARM_MONITOR_ON
}alarmMonitorStatus_t;

extern alarmMonitorStatus_t alarmMonitorStatus;
extern void(*alarmState)();

void AlarmMonitorInit();
STATE_DEFINE(AlarmOff);
STATE_DEFINE(AlarmOn);


#endif /* ALARMMONITOR_H_ */
