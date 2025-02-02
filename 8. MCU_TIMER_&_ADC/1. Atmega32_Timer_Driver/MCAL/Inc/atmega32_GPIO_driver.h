/*
 * atmega32_GPIO_driver.h
 *
 * Created: 05/12/2024 7:54:33 PM
 *  Author: Mohamed Elsayed 
 */ 


#ifndef ATMEGA32_GPIO_DRIVER_H
#define ATMEGA32_GPIO_DRIVER_H

#include <avr/io.h>

// GPIO Port Definitions
typedef enum {
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D
} GPIO_Port;

// GPIO Pin Direction
typedef enum {
	GPIO_PIN_INPUT,
	GPIO_PIN_OUTPUT
} GPIO_Direction;

// GPIO Pin State
typedef enum {
	GPIO_PIN_LOW,
	GPIO_PIN_HIGH
} GPIO_State;

// Function Prototypes
void GPIO_InitPin(GPIO_Port port, uint8_t pinNumber, GPIO_Direction direction);
void GPIO_WritePin(GPIO_Port port, uint8_t pinNumber, GPIO_State state);
GPIO_State GPIO_ReadPin(GPIO_Port port, uint8_t pinNumber);
void GPIO_TogglePin(GPIO_Port port, uint8_t pinNumber);

#endif // ATMEGA32_GPIO_DRIVER_H
