/*
 * atmega32_UART_driver.c
 *
 * Created: 10/12/2024 11:59:06 AM
 *  Author: Mohamed Elsayed
 */ 


#include "atmega32_UART_driver.h"

// UART ISR Variables

#define BUFFER_SIZE 20
static volatile uint8_t uart_buffer[BUFFER_SIZE];
static volatile uint8_t buffer_index = 0;

void UART_Init(UART_config_t *uartConfig) {
	// Disable global interrupts
	cli();

	// Set the baud rate
	RESET_BIT(UCSRA, U2X);   // Ensure normal speed mode (U2X = 0)
	uint16_t UBRR = (F_CPU / (16UL * uartConfig->baud_rate)) - 1;
	UBRRL = (uint8_t)(UBRR & 0xFF);   // Correct lower byte
	UBRRH = (uint8_t)((UBRR >> 8) & 0xFF); // Correct upper byte

	// Select Synchronous or Asynchronous mode
	if (uartConfig->mode == UART_ASYNC_MODE) {
		RESET_BIT(UCSRC, UMSEL); // Asynchronous mode
	} 
	else {
		SET_BIT(UCSRC, UMSEL);   // Synchronous mode
	}

	// Configure parity mode
	UCSRC &= ~(0b11 << UPM0); // Clear UPM0 and UPM1
	UCSRC |= ((uartConfig->parity_type & 0x3) << UPM0);

	// Configure stop bits
	UCSRC &= ~(1 << USBS); // Clear USBS
	UCSRC |= (uartConfig->stop_bits << USBS);

	// Configure character size
	UCSRC &= ~(0b11 << UCSZ0); // Clear UCSZ0 and UCSZ1
	UCSRC |= ((uartConfig->data_bits & 0x3) << UCSZ0);
	if (uartConfig->data_bits == UART_9_BIT_DATA) {
		SET_BIT(UCSRB, UCSZ2); // Enable 9th bit
	} 
	else {
		RESET_BIT(UCSRB, UCSZ2); // Disable 9th bit
	}

	// Enable transmitter and receiver
	SET_BIT(UCSRB, TXEN); // Enable transmitter
	SET_BIT(UCSRB, RXEN); // Enable receiver

	// Configure interrupts if requested
	if (uartConfig->rx_enable_interrupt == UART_ENABLE_INTERRUPT) {
		SET_BIT(UCSRB, RXCIE); // Enable RX complete interrupt
	}
	if (uartConfig->tx_enable_interrupt == UART_ENABLE_INTERRUPT) {
		SET_BIT(UCSRB, TXCIE); // Enable TX complete interrupt
	}

	// Re-enable global interrupts
	sei();
}


void UART_TransmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!READ_BIT(UCSRA, UDRE)); // Wait until the buffer is ready
	UDR = data;                    // Write the data to the USART data register
}

uint8_t UART_ReceiveByte(void) {
	/* Wait for data to be received */
	while (!READ_BIT(UCSRA, RXC));  // Wait until data is received
	return UDR;                    // Return the received data
}

void UART_TransmitString(const uint8_t *str) {
	while (*str) {                 // Loop until null terminator is found
		UART_TransmitByte(*str++); // Transmit each character
	}
}


void USART_ReceiveString(char *buffer, uint16_t max_length) {
	uint16_t index = 0;  // Buffer index
	char received_char;

	while (1) {
		received_char = UART_ReceiveByte();

		if (received_char == '\n' || received_char == '\r') {
			buffer[index] = '\0';  // Null-terminate the string
			break;
		}

		if (index < (max_length - 1)) {
			buffer[index++] = received_char;
		} 
		else{
			buffer[index] = '\0';
			break;
		}
	}
}



// UART RX ISR
ISR(USART_RXC_vect) {
	char received_char = UART_ReceiveByte();

	if (received_char == '\n' || buffer_index >= BUFFER_SIZE - 1 || received_char == '\r') {
		uart_buffer[buffer_index] = '\0';  // Null-terminate the string
		buffer_index = 0;                 // Reset index

		// Clear LCD and display received string
		uint8_t clear_buf[] = "                    ";
		lcd_send_string_pos(clear_buf, 2, 1);
		lcd_send_string_pos(clear_buf, 3, 1);
		lcd_send_string_pos(clear_buf, 4, 1);
		lcd_send_string_pos(uart_buffer, 2, 1);
	} 
	else {
		uart_buffer[buffer_index++] = received_char;  // Add char to buffer
	}
}