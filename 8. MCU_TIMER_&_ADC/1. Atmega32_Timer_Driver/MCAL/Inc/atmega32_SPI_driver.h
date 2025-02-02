/*
 * atmega32_SPI_driver.h
 *
 * Created: 21/12/2024 7:37:49 AM
 *  Author: Mohamed Elsayed
 */ 


#ifndef ATMEGA32_SPI_DRIVER_H_
#define ATMEGA32_SPI_DRIVER_H_


// Includes
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "Util.h"
#include "atmega32_GPIO_driver.h"



//#define SPI_MASTER_MODE
#define SPI_SLAVE_MODE


#define MOSI		5
#define MISO		6
#define SCK			7
#define SS			4



// SPI initialization function (Master Mode)
void SPI_init(void);

// SPI transmit function
void SPI_transmit(uint8_t data);

// SPI receive function
uint8_t SPI_receive(void);

// SPI transmit and receive function (simultaneously)
uint8_t SPI_transmitReceive(uint8_t data);


#endif /* ATMEGA32_SPI_DRIVER_H_ */