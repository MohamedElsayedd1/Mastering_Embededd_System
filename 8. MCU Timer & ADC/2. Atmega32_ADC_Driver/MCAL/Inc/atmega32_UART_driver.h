/*
 * atmega32_UART_driver.h
 *
 * Created: 10/12/2024 11:57:50 AM
 *  Author: Mohamed Elsayed
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

// Includes
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h> 
#include "Util.h"
#include "atmega32_HAL_LCD.h"

// UART configuration structure & enums
typedef enum{
	UART_5_BIT_DATA = 0,
	UART_6_BIT_DATA = 1,
	UART_7_BIT_DATA = 2,
	UART_8_BIT_DATA = 3,
	UART_9_BIT_DATA = 7,
}UART_data_bits_t;

typedef enum{
	UART_ONE_STOP_BIT,
	UART_TWO_STOP_BIT
}UART_stop_bits_t;

typedef enum{
	UART_NO_PARITY = 0,
	UART_EVEN_PARITY = 2,
	UART_ODD_PARITY = 3
}UART_parity_t;

typedef enum{
	UART_ASYNC_MODE,
	UART_SYNC_MODE
}UART_mode_t;

typedef enum{
	UART_DISABLED_INTERRUPT,
	UART_ENABLE_INTERRUPT
}UART_interrupt_t;

typedef struct {
	uint32_t baud_rate;
	UART_data_bits_t data_bits;
	UART_stop_bits_t stop_bits;
	UART_parity_t parity_type;
	UART_mode_t mode;
	UART_interrupt_t rx_enable_interrupt;
	UART_interrupt_t tx_enable_interrupt;
}UART_config_t;


// API
void UART_Init(UART_config_t *uartConfig);
void UART_TransmitByte(uint8_t data);
uint8_t UART_ReceiveByte(void);
void UART_TransmitString(const uint8_t *str);
void USART_ReceiveString(char *buffer, uint16_t max_length);


#endif /* INCFILE1_H_ */