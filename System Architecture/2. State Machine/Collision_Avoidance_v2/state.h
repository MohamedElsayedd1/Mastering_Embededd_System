/*
 * state.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h> // for rand() and srand()
#include <time.h>   // for time()

#define STATE_DEFINE(_stateFunction) void state_##_stateFunction()
#define STATE(_stateFunctionName) state_##_stateFunctionName

void US_Set_distance(int distance);

#endif /* STATE_H_ */
