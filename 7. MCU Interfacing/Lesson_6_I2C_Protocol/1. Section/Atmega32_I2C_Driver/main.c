/*
 * main.c
 *
 * Created: 05/12/2024 7:51:50 PM
 *  Author: Mohamed Elsayed
 */ 

#include <util/delay.h>
#include <xc.h>

#include "atmega32_GPIO_driver.h"
#include "atmega32_HAL_LCD.h"
#include "atmega32_UART_driver.h"
#include "atmega32_I2C_driver.h"

#define SLAVE_ADDRESS 0xD0

void display_number(uint8_t number) {
	PORTB = number; 
}

int main(void) {
	// Initialize Master or Slave based on the role
	#if I2C_MODE == I2C_MASTER_MODE
	I2C_MasterInit();
	uint8_t received_data = 0;
	DDRB = 0xFF; // Set PORTB as output for display
	while (1) {
		I2C_MasterRead(SLAVE_ADDRESS, &received_data); // Receive data from the master
		display_number(received_data); // Display the received number
	}
	#else
	I2C_SlaveInit(SLAVE_ADDRESS);
	uint8_t number = 1;
	while (1) {
		I2C_SlaveWrite(number);
		number++;
		if (number > 99) {
			number = 1;
		}
		_delay_ms(1000);
	}
	#endif

	return 0;
}


