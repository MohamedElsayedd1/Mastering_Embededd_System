/*
 * DC_Motor.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "DC_Motor.h"

static int DC_speed = 0;
void (*DC_State)();

void DC_init()
{
	//init PWM driver
	printf("DC_init\n");
}

void DC_Motor_Set_Speed(int speed){
	DC_speed = speed;
	DC_State = STATE(DC_MOTOR_BUSY);
	printf("CA --------- Speed = %d -------> DC \n", DC_speed);
}

STATE_DEFINE(DC_MOTOR_IDLE){
	DC_State = STATE(DC_MOTOR_IDLE);
}

STATE_DEFINE(DC_MOTOR_BUSY){
	// State_Name
	DC_State = STATE(DC_MOTOR_IDLE);
}
