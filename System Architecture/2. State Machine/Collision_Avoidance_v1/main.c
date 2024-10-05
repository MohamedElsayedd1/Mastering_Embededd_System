/*
 * main.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed Elsayed
 */

#include "Collision_Avoidance.h"

void setup(){
	CA_State = STATE(CA_Waiting);

}

int main(){
	setup();
	while(1){
		CA_State();
		// Add delay
		for(volatile int i = 0; i < 100; i++){
			for(volatile int j = 0; j < 3180; j++);
		}
	}


	return 0;
}
