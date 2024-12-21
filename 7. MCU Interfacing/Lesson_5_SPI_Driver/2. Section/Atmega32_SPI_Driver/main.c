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

int main(void) {
	// SPI Initialize
	SPI_init();
	// LCD Initialize
	lcd_initialize();
	
	//char TransmitterChar = 'A';
	
	char TransmitterChar = 'Z';
	
	char transmitted[] = "Transmit : ";
	char Recieved[] = "Receive : ";
	
	
	while (1) {
		lcd_send_string_pos(transmitted, 1, 1);
		lcd_send_string_pos(Recieved, 2, 1);
		
		uint8_t RecievedChar = SPI_receive();
		lcd_send_char_data_pos(RecievedChar, 2, 12);
		
		// Transmit data and update TransmitterChar
		SPI_transmit(TransmitterChar);
		lcd_send_char_data_pos(TransmitterChar, 1, 12);
		TransmitterChar--;
		if (TransmitterChar < 'A') {
			TransmitterChar = 'Z';
		}
		
	}

	return 0;
}

