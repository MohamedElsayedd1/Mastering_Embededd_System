/*
 * main.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "Collision_Avoidance.h"
#include "Ultrasonic_Sensor.h"
#include "DC_Motor.h"

void setup(){
	US_init();
	DC_init();
	CA_State = STATE(CA_Waiting);
	US_State = STATE(ULTRASONIC_BUSY);
	DC_State = STATE(DC_MOTOR_IDLE);
}

int main(){
	setup();
	while(1){
		US_State();
		CA_State();
		DC_State();
		// Add delay
		for(volatile int i = 0; i < 100; i++){
			for(volatile int j = 0; j < 3180; j++);
		}
	}


	return 0;
}
