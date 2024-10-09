/*
 * Collision_Avoidance.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "state.h"

typedef enum{
	COLLISION_AVOIDANCE_WAITING,
	COLLISION_AVOIDANCE_DRIVING
}CA_status_t;

STATE_DEFINE(CA_Waiting);
STATE_DEFINE(CA_Driving);

extern void (*CA_State)();

void UlraSonic_Read_Random_Values(int min, int max);

#endif /* COLLISION_AVOIDANCE_H_ */
