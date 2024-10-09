/*
 * state.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Dubai Store
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdio.h>

#define STATE_DEFINE(_stateFun) void state##_stateFun()
#define STATE(_stateFunName) state##_stateFunName

void ReadPressureValue(int p);
void HighPressureDetected();
void CheckPressureValue();

#endif /* STATE_H_ */
