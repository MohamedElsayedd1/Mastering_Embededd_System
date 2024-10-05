/*
 * Collision_Avoidance.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "Collision_Avoidance.h"

int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;
CA_status_t CA_status;
void (*CA_State)();

STATE_DEFINE(CA_Waiting){
	CA_State = STATE(CA_Waiting);
	CA_speed = 0;
	printf("COLLISION AVOIDANCE: Waiting, speed = %d, distance = %d\n", CA_speed, CA_distance);
	UlraSonic_Read_Random_Values(40, 60);
	CA_State = (CA_distance <= CA_threshold) ? STATE(CA_Waiting) : STATE(CA_Driving);
}

STATE_DEFINE(CA_Driving){
	CA_State = STATE(CA_Driving);
	CA_speed = 30;
	printf("COLLISION AVOIDANCE: Driving, speed = %d, distance = %d\n", CA_speed, CA_distance);
	UlraSonic_Read_Random_Values(40, 60);
	CA_State = (CA_distance <= CA_threshold) ? STATE(CA_Waiting) : STATE(CA_Driving);
}

void UlraSonic_Read_Random_Values(int min, int max){
	CA_distance = min + rand() % (max - min + 1);
}
