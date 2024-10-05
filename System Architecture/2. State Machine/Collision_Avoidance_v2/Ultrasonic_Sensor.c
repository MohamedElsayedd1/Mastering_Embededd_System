/*
 * Ultrasonic_Sensor.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "Ultrasonic_Sensor.h"

static int US_distance = 0;
void (*US_State)();
US_status_t us_status;

void US_init(){
	//init Ultrasonic driver
	printf("US_init\n");
}

void UlraSonic_Read_Random_Values(int min, int max){
	US_distance = min + rand() % (max - min + 1);
}

STATE_DEFINE(ULTRASONIC_BUSY){
	us_status = ULTRASONIC_BUSY;
	UlraSonic_Read_Random_Values(40, 60);
	US_Set_distance(US_distance);
	US_State = STATE(ULTRASONIC_BUSY);
}


