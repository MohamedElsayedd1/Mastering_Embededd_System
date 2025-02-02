/*
 * atmega32_I2C_driver.c
 *
 * Created: 24/01/2025 11:21:39 PM
 *  Author: Mohamed Elsayed
 */ 

#include "atmega32_I2C_driver.h"


void I2C_MasterInit(void) {
	TWSR = I2C_PRESCALER_1;                 // Set prescaler to 1
	TWBR = ((F_CPU / I2C_SCL_CLOCK) - 16) / 2; // Set bit rate
	TWCR = (1 << TWEN);                     // Enable TWI
}

void I2C_SlaveInit(uint8_t slave_address) {
	TWAR = slave_address;            // Set slave address
	TWCR = (1 << TWEN) | (1 << TWEA);       // Enable TWI and ACK
}

void I2C_Start(void) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send START condition
	while (!(TWCR & (1 << TWINT)));          // Wait for TWINT flag
}

void I2C_Stop(void) {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send STOP condition
	while (TWCR & (1 << TWSTO));             // Wait for STOP to complete
}

void I2C_Write(uint8_t data) {
	TWDR = data;                             // Load data into TWDR
	TWCR = (1 << TWEN) | (1 << TWINT);       // Start transmission
	while (!(TWCR & (1 << TWINT)));          // Wait for TWINT flag
}

uint8_t I2C_Read(uint8_t ack) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (ack ? (1 << TWEA) : 0); // Start read with/without ACK
	while (!(TWCR & (1 << TWINT)));          // Wait for TWINT flag
	return TWDR;                             // Return received data
}

uint8_t I2C_GetStatus(void) {
	return TWSR & 0xF8;                      // Mask prescaler bits
}

void I2C_MasterWrite(uint8_t slave_address, uint8_t data) {
	I2C_Start();                             // Send START condition
	I2C_Write(slave_address + 0);     // Send slave address with write flag
	while (I2C_GetStatus() != TW_MT_SLA_ACK);
	I2C_Write(data);  
	while (I2C_GetStatus() != TW_MT_DATA_ACK);  
	I2C_Stop();                              // Send STOP condition
}

void I2C_MasterRead(uint8_t slave_address, uint8_t *buffer) {
	I2C_Start();                             // Send START condition
	I2C_Write(slave_address + 1);     // Send slave address with read flag
	while (I2C_GetStatus() != TW_MR_SLA_ACK) return;
	
	*buffer = I2C_Read(0); // Read data with ACK

	I2C_Stop();                              // Send STOP condition
}

void I2C_SlaveWrite(uint8_t data) {
	while (!(TWCR & (1 << TWINT)));      // Wait for TWINT flag
	if ((TWSR & 0xF8) != TW_ST_SLA_ACK && (TWSR & 0xF8) != TW_ST_DATA_ACK) return;
	TWDR = data;                      // Load data into TWDR
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Send data
}

void I2C_SlaveRead(uint8_t *buffer) {
	while (!(TWCR & (1 << TWINT)));      // Wait for TWINT flag
	if ((TWSR & 0xF8) != TW_SR_SLA_ACK && (TWSR & 0xF8) != TW_SR_DATA_ACK) return;
	*buffer = TWDR;                    // Read data from TWDR
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Send ACK
}


