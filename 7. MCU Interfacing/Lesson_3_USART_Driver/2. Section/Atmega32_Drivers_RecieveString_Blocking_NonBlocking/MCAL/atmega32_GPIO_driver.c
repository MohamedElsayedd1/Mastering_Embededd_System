/*
 * CFile1.c
 *
 * Created: 05/12/2024 7:55:43 PM
 *  Author: Mohamed Elsayed
 */ 

#include "atmega32_GPIO_driver.h"

void GPIO_InitPin(GPIO_Port port, uint8_t pinNumber, GPIO_Direction direction) {
	switch (port) {
		case GPIO_PORT_A:
		if (direction == GPIO_PIN_OUTPUT) {
			DDRA |= (1 << pinNumber); // Set pin as output
			} else {
			DDRA &= ~(1 << pinNumber); // Set pin as input
		}
		break;

		case GPIO_PORT_B:
		if (direction == GPIO_PIN_OUTPUT) {
			DDRB |= (1 << pinNumber);
			} else {
			DDRB &= ~(1 << pinNumber);
		}
		break;

		case GPIO_PORT_C:
		if (direction == GPIO_PIN_OUTPUT) {
			DDRC |= (1 << pinNumber);
			} else {
			DDRC &= ~(1 << pinNumber);
		}
		break;

		case GPIO_PORT_D:
		if (direction == GPIO_PIN_OUTPUT) {
			DDRD |= (1 << pinNumber);
			} else {
			DDRD &= ~(1 << pinNumber);
		}
		break;
	}
}

void GPIO_WritePin(GPIO_Port port, uint8_t pinNumber, GPIO_State state) {
	switch (port) {
		case GPIO_PORT_A:
		if (state == GPIO_PIN_HIGH) {
			PORTA |= (1 << pinNumber); // Set pin high
			} else {
			PORTA &= ~(1 << pinNumber); // Set pin low
		}
		break;

		case GPIO_PORT_B:
		if (state == GPIO_PIN_HIGH) {
			PORTB |= (1 << pinNumber);
			} else {
			PORTB &= ~(1 << pinNumber);
		}
		break;

		case GPIO_PORT_C:
		if (state == GPIO_PIN_HIGH) {
			PORTC |= (1 << pinNumber);
			} else {
			PORTC &= ~(1 << pinNumber);
		}
		break;

		case GPIO_PORT_D:
		if (state == GPIO_PIN_HIGH) {
			PORTD |= (1 << pinNumber);
			} else {
			PORTD &= ~(1 << pinNumber);
		}
		break;
	}
}

GPIO_State GPIO_ReadPin(GPIO_Port port, uint8_t pinNumber) {
	GPIO_State state = GPIO_PIN_LOW;

	switch (port) {
		case GPIO_PORT_A:
		state = (PINA & (1 << pinNumber)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
		break;

		case GPIO_PORT_B:
		state = (PINB & (1 << pinNumber)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
		break;

		case GPIO_PORT_C:
		state = (PINC & (1 << pinNumber)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
		break;

		case GPIO_PORT_D:
		state = (PIND & (1 << pinNumber)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
		break;
	}

	return state;
}

void GPIO_TogglePin(GPIO_Port port, uint8_t pinNumber) {
	switch (port) {
		case GPIO_PORT_A:
		PORTA ^= (1 << pinNumber); // Toggle pin
		break;

		case GPIO_PORT_B:
		PORTB ^= (1 << pinNumber);
		break;

		case GPIO_PORT_C:
		PORTC ^= (1 << pinNumber);
		break;

		case GPIO_PORT_D:
		PORTD ^= (1 << pinNumber);
		break;
	}
}
