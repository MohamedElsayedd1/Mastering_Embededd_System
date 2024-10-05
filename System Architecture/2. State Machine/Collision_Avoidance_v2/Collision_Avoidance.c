/*
 * Collision_Avoidance.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "Collision_Avoidance.h"
#include "DC_Motor.h"

static int CA_speed = 0;
static int CA_distance = 0;
static int CA_threshold = 50;
CA_status_t CA_status;
void (*CA_State)();

void US_Set_distance(int distance){
	CA_distance = distance;
	CA_State = (CA_distance <= CA_threshold) ? STATE(CA_Waiting) : STATE(CA_Driving);
	printf("US --------- distance = %d -------> CA \n", CA_distance);
}

STATE_DEFINE(CA_Waiting){
	CA_State = STATE(CA_Waiting);
	CA_speed = 0;
	DC_Motor_Set_Speed(CA_speed);
	printf("COLLISION AVOIDANCE: Waiting, speed = %d, distance = %d\n", CA_speed, CA_distance);
}

STATE_DEFINE(CA_Driving){
	CA_State = STATE(CA_Driving);
	CA_speed = 30;
	DC_Motor_Set_Speed(CA_speed);
	printf("COLLISION AVOIDANCE: Driving, speed = %d, distance = %d\n", CA_speed, CA_distance);
}


