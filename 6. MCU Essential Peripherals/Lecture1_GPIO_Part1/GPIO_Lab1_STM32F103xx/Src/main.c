/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>

#define READ_BIT(REG, BIT_POS)		((REG >> BIT_POS) & 0X01)
#define TOGGLE_BIT(REG, BIT_POS)	(REG ^= (1 << BIT_POS))

#define RCC_BASE_ADDRESS		0x40021000
#define RCC_APB2ENR				*((volatile uint32_t *)(RCC_BASE_ADDRESS + 0x18))

#define GPIOA_BASE_ADDRESS 		0x40010800
#define GPIOB_BASE_ADDRESS 		0x40010C00
#define GPIOA_CRL				*((volatile uint32_t *)(GPIOA_BASE_ADDRESS + 0x00))
#define GPIOB_CRL				*((volatile uint32_t *)(GPIOB_BASE_ADDRESS + 0x00))
#define GPIOA_CRH				*((volatile uint32_t *)(GPIOA_BASE_ADDRESS + 0x04))
#define GPIOB_CRH				*((volatile uint32_t *)(GPIOB_BASE_ADDRESS + 0x04))
#define GPIOA_IDR				*((volatile uint32_t *)(GPIOA_BASE_ADDRESS + 0x08))
#define GPIOB_IDR				*((volatile uint32_t *)(GPIOB_BASE_ADDRESS + 0x08))
#define GPIOA_ODR				*((volatile uint32_t *)(GPIOA_BASE_ADDRESS + 0x0C))
#define GPIOB_ODR				*((volatile uint32_t *)(GPIOB_BASE_ADDRESS + 0x0C))

typedef enum{
	GPIO_LOW_STATE,
	GPIO_HIGH_STATE
}gpio_state_t;

void clock_Init(){
	RCC_APB2ENR |= (1 << 2); // IO port A clock enabled
	RCC_APB2ENR |= (1 << 3); // IO port B clock enabled
}

void GPIO_Init(){
	// Configure PA1 and PA13 as Floating Input
	// 00: Input mode (reset state)
	GPIOA_CRL &= ~(0b11 << 4);
	GPIOA_CRH &= ~(0b11 << 20);
	// 01: Floating input (reset state)
	GPIOA_CRL &= ~(0b11 << 6);
	GPIOA_CRL |= (0b01 << 6);
	GPIOA_CRH &= ~(0b11 << 22);
	GPIOA_CRH |= (0b01 << 22);

	// Configure PB1 and PB13 as Push-Pull Output
	// 01: Output mode, max speed 10 MHz.
	GPIOB_CRL &= ~(0b11 << 4);
	GPIOB_CRL |= (0b10 << 4);
	GPIOB_CRH &= ~(0b11 << 20);
	GPIOB_CRH |= (0b10 << 20);
	// 00: General purpose output push-pull
	GPIOB_CRL &= ~(0b11 << 6);
	GPIOB_CRH &= ~(0b11 << 22);
	GPIOB_ODR |= (1 << 1);
	GPIOB_ODR |= (1 << 13);
}

gpio_state_t ReadPushButton1(void){
	// Read the logic of PA1 pin -> Push-Up Resistor (High)
	gpio_state_t btn1_state = READ_BIT(GPIOA_IDR, 1);
	return btn1_state;
}

gpio_state_t ReadPushButton2(void){
	// Read the logic of PA13 pin -> Push-Down Resistor (Low)
	gpio_state_t btn2_state = READ_BIT(GPIOA_IDR, 13);
	return btn2_state;
}

void toggleLed1(void){
	// Toggle Led connected to PB1
	TOGGLE_BIT(GPIOB_ODR, 1);
}

void toggleLed2(void){
	// Toggle Led connected to PB13
	TOGGLE_BIT(GPIOB_ODR, 13);
}

void delay(volatile int count) {
    while(count--);
}

uint32_t btn1_prev = GPIO_HIGH_STATE;
uint32_t btn2_prev = GPIO_LOW_STATE;

int main(void)
{
	clock_Init();
	GPIO_Init();
    while(1){
    	// Read Push-Button 1, 2 Logic
    	// Read PA1 pin
    	gpio_state_t btn1_current = ReadPushButton1();
    	// Check on Push-Button 1 -> PA1 pin
    	if(btn1_current == GPIO_LOW_STATE && btn1_prev == GPIO_HIGH_STATE){
    		toggleLed1();
    	}
    	btn1_prev = btn1_current;
    	// Another Solution
//    	if(btn1_current == GPIO_LOW_STATE){
//    		toggleLed1();
//    		while(btn1_current == GPIO_LOW_STATE);
//    	}

    	// Read PA13 pin
    	gpio_state_t btn2_current = ReadPushButton2();
    	// Check on Push-Button 2 -> PA13 pin
		if(btn2_current == GPIO_HIGH_STATE){
			toggleLed2();
		}
		delay(100000);

    }
}
