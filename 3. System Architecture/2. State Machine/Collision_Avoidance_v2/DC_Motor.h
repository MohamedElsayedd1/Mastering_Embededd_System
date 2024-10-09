/*
 * DC_Motor.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "state.h"

typedef enum{
	DC_MOTOR_IDLE,
	DC_MOTOR_BUSY
}DC_status_t;

STATE_DEFINE(DC_MOTOR_IDLE);
STATE_DEFINE(DC_MOTOR_BUSY);

extern void (*DC_State)();

void DC_init();
void DC_Motor_Set_Speed(int speed);


#endif /* DC_MOTOR_H_ */
