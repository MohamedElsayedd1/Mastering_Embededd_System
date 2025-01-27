/*
 * stm32f103x6_SLAVE_EEPROM_Driver..c
 *
 *  Created on: Jan 27, 2025
 *      Author: Mohamed Elsayed
 */


/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_SLAVE_EEPROM_Driver.h"

/* ================================================================ */
/* ======================= Global Variables ======================= */
/* ================================================================ */


/* ================================================================ */
/* ======================== Static APIs =========================== */
/* ================================================================ */


/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

void HAL_EEPROM_Init(void){
	I2C_Config_t I2C1_Config;

	I2C1_Config.AckStatus = I2C_ACK_ENABLE;
	I2C1_Config.ErrorInterruptStatus = I2C_ERROR_INTERRUPT_DISABLE;
	I2C1_Config.EventInterruptStatus = I2C_EVENT_INTERRUPT_DISABLE;
	I2C1_Config.GeneralCallStatus = I2C_GENERAL_CALL_ENABLE;
	I2C1_Config.I2C_Clock = 100000;
	I2C1_Config.I2C_Mode = I2C_MASTER_MODE;
	I2C1_Config.MasterModeSelect = I2C_SM_MODE;
	I2C1_Config.SMBusMode = I2C_MODE_ENABLE;

	MCAL_I2C_Init(I2C1, &I2C1_Config);
}

void HAL_EEPROM_Write_N_Bytes(uint16 memoryAddress, uint8 *dataOut, uint8 Nbytes){
	// Generate START condition
	MCAL_I2C_Master_Transmit_Start(I2C1);

	// Send EEPROM slave address with write direction
	MCAL_I2C_Master_Transmit_Address(I2C1, EXTERNAL_EEPROM_SLAVE_ADDRESS, I2C_DIRECTION_WRITE);

	// Send memory address (high byte and low byte)
	MCAL_Transmit_Byte(I2C1, ((memoryAddress >> 8) & 0xFF)); // High Byte
	MCAL_Transmit_Byte(I2C1, ((memoryAddress) & 0xFF)); // Low Byte

	// Transmit data bytes
	for (uint8 i = 0; i < Nbytes; i++) {
		MCAL_Transmit_Byte(I2C1, dataOut[i]); // Transmit each byte
	}

	// Wait till last byte is transferred
	while (!READ_BIT(I2C1->SR1, 2)); // Wait until BTF flag is set

	// Generate STOP condition
	MCAL_I2C_Master_Transmit_Stop(I2C1);
}

void HAL_EEPROM_Read_N_Bytes(uint16 memoryAddress, uint8 *dataIn, uint8 Nbytes){
	// Generate START condition
	MCAL_I2C_Master_Transmit_Start(I2C1);

	// Send EEPROM slave address with write direction
	MCAL_I2C_Master_Transmit_Address(I2C1, EXTERNAL_EEPROM_SLAVE_ADDRESS, I2C_DIRECTION_WRITE);

	// Send memory address (high byte and low byte for 16-bit addressing)
	MCAL_Transmit_Byte(I2C1, ((memoryAddress >> 8) & 0xFF)); // High Byte
	MCAL_Transmit_Byte(I2C1, ((memoryAddress) & 0xFF)); // Low Byte

	// Generate Repeated START condition
	MCAL_I2C_Master_Transmit_RepeatedStart(I2C1);;

	// Send EEPROM slave address with read direction
	MCAL_I2C_Master_Transmit_Address(I2C1, EXTERNAL_EEPROM_SLAVE_ADDRESS, I2C_DIRECTION_READ);

	// Recieve data bytes
	for(uint8 i = 0; i < Nbytes; i++){
		if(i == (Nbytes - 1)){
			dataIn[i] = MCAL_Recieve_With_NACK(I2C1);
		}
		else{
			dataIn[i] = MCAL_Recieve_With_ACK(I2C1);
		}
	}

	// Generate STOP condition
	MCAL_I2C_Master_Transmit_Stop(I2C1);
}
