/*
 * GPIO.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Dubai Store
 */


#include "GPIO.h"

void Delayms(int count)
{
	while (count--) {
        __asm("nop");  // Assembly instruction for "No Operation", used to waste time
    }
}

int getPressureVal(){
	return (GPIOA_IDR & 0xFF);
}

void Set_Alarm_actuator(int i){
	if (i == 1){
		SET_BIT(GPIOA_ODR,13);
	}
	else if (i == 0){
		RESET_BIT(GPIOA_ODR,13);
	}
}

void GPIO_INITIALIZATION (){
	SET_BIT(APB2ENR, 2);
	GPIOA_CRL &= 0xFF0FFFFF;
	GPIOA_CRL |= 0x00000000;
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x22222222;
}
