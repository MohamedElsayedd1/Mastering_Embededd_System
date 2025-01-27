/*
 * stm32f103x6_SLAVE_EEPROM_Driver.h
 *
 *  Created on: Jan 27, 2025
 *      Author: Mohamed Elsayed
 */

#ifndef EEPROM_STM32F103X6_SLAVE_EEPROM_DRIVER_H_
#define EEPROM_STM32F103X6_SLAVE_EEPROM_DRIVER_H_


/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */
#include "stm32f103x6_I2C_driver.h"
#include "stm32f103x6.h"
#include "Util.h"
#include "Platform_Types.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */


/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */
#define EXTERNAL_EEPROM_SLAVE_ADDRESS		0x2A

/* ================================================================ */
/* ============= APIs Supported by "MCAL I2C DRIVER"============= */
/* ================================================================ */
void HAL_EEPROM_Init(void);
void HAL_EEPROM_Write_N_Bytes(uint16 memoryAddress, uint8 *dataOut, uint8 Nbytes);
void HAL_EEPROM_Read_N_Bytes(uint16 memoryAddress, uint8 *dataIn, uint8 Nbytes);

#endif /* EEPROM_STM32F103X6_SLAVE_EEPROM_DRIVER_H_ */
