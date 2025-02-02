/*
 * atmega32_I2C_driver.h
 *
 * Created: 24/01/2025 11:21:10 PM
 *  Author: Mohamed Elsayed
 */ 


#ifndef ATMEGA32_I2C_DRIVER_H_
#define ATMEGA32_I2C_DRIVER_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "Util.h"

#define I2C_MASTER_MODE  0X01
#define I2C_SLAVE_MODE   0X00
#define I2C_MODE I2C_SLAVE_MODE

#define F_CPU 16000000UL    // CPU Frequency
#define I2C_SCL_CLOCK 100000 // SCL frequency in Hz

// Prescaler values
#define I2C_PRESCALER_1 0x00
#define I2C_PRESCALER_4 0x01
#define I2C_PRESCALER_16 0x02
#define I2C_PRESCALER_64 0x03

// I2C status codes (partial)
#define TW_START 0x08
#define TW_REP_START 0x10
#define TW_MT_SLA_ACK 0x18
#define TW_MT_SLA_NACK 0x20
#define TW_MT_DATA_ACK 0x28
#define TW_MT_DATA_NACK 0x30
#define TW_MR_SLA_ACK 0x40
#define TW_MR_SLA_NACK 0x48
#define TW_MR_DATA_ACK 0x50
#define TW_MR_DATA_NACK 0x58
#define TW_SR_SLA_ACK 0x60
#define TW_SR_DATA_ACK 0x80
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xB8

// Function prototypes

/**
 * @brief Initialize I2C in Master mode.
 */
void I2C_MasterInit(void);

/**
 * @brief Initialize I2C in Slave mode.
 * @param slave_address The 7-bit slave address.
 */
void I2C_SlaveInit(uint8_t slave_address);

/**
 * @brief Send a START condition on the I2C bus.
 */
void I2C_Start(void);

/**
 * @brief Send a STOP condition on the I2C bus.
 */
void I2C_Stop(void);

/**
 * @brief Write a byte of data to the I2C bus.
 * @param data The data byte to write.
 */
void I2C_Write(uint8_t data);

/**
 * @brief Read a byte of data from the I2C bus.
 * @param ack 1 to send ACK, 0 to send NACK.
 * @return The received data byte.
 */
uint8_t I2C_Read(uint8_t ack);

/**
 * @brief Get the current I2C status.
 * @return The status code from the TWSR register.
 */
uint8_t I2C_GetStatus(void);

/**
 * @brief Master mode: Write data to a slave device.
 * @param slave_address The 7-bit slave address.
 * @param data Pointer to the data array to send.
 */
void I2C_MasterWrite(uint8_t slave_address, uint8_t data);

/**
 * @brief Master mode: Read data from a slave device.
 * @param slave_address The 7-bit slave address.
 * @param buffer Pointer to the buffer to store received data.
 */
void I2C_MasterRead(uint8_t slave_address, uint8_t *buffer);

/**
 * @brief Slave mode: Write data to the master.
 * @param data Pointer to the data array to send.
 */
void I2C_SlaveWrite(uint8_t data);

/**
 * @brief Slave mode: Read data from the master.
 * @param buffer Pointer to the buffer to store received data.
 */
void I2C_SlaveRead(uint8_t *buffer);


#endif /* ATMEGA32_I2C_DRIVER_H_ */