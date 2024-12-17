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

// Define a UART configuration instance
UART_config_t myUart = {
	.baud_rate = 9600,                 // Set baud rate to 9600
	.data_bits = UART_8_BIT_DATA,      // 8 data bits
	.stop_bits = UART_ONE_STOP_BIT,    // 1 stop bit
	.parity_type = UART_NO_PARITY,     // No parity
	.mode = UART_ASYNC_MODE,           // Asynchronous mode
	.rx_enable_interrupt = UART_DISABLED_INTERRUPT,  // Disable RX interrupt
	.tx_enable_interrupt = UART_DISABLED_INTERRUPT // Disable TX interrupt
};

int main(void) {
	// LCD Initialize
 	lcd_initialize();
	UART_Init(&myUart);
	
	
    uint8_t buff[20];
	
	
	while (1) {
		USART_ReceiveString(buff, 20);
		
		// Clear LCD and display received string
		uint8_t clear_buf[] = "                    ";
		lcd_send_string_pos(clear_buf, 2, 1);
		lcd_send_string_pos(clear_buf, 3, 1);
		lcd_send_string_pos(clear_buf, 4, 1);
		lcd_send_string_pos(buff, 2, 1);
	
	}

	return 0;
}
