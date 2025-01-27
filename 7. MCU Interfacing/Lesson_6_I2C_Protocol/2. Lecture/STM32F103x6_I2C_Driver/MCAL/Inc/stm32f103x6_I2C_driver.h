/*
 * stm32f103x6_I2C_driver.h
 *
 *  Created on: Dec 19, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_SPI_DRIVER_H_
#define INC_STM32F103X6_SPI_DRIVER_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6.h"
#include "stm32f103x6_RCC_driver.h"
#include "stm32f103x6_GPIO_driver.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef enum{
	I2C_MASTER_MODE,
	I2C_SLAVE_MODE
}I2C_Mode_t;

typedef enum{
	I2C_NACK_ENABLE,
	I2C_ACK_ENABLE
}I2C_AckStatus_t;

typedef enum{
	I2C_CLOCK_STRETCH_ENABLE,
	I2C_CLOCK_STRETCH_DISABLE
}I2C_ClockStretchStatus_t;

typedef enum{
	I2C_GENERAL_CALL_DISABLE,
	I2C_GENERAL_CALL_ENABLE,
}I2C_GeneralCallStatus_t;

typedef enum{
	I2C_MODE_ENABLE,
	SMBUS_MODE_ENABLE
}I2C_SMBusMode_t;

typedef enum{
	I2C_SM_MODE,
	I2C_FM_MODE
}I2C_MasterModeSelect_t;

typedef enum{
	I2C_EVENT_INTERRUPT_DISABLE,
	I2C_EVENT_INTERRUPT_ENABLE
}I2C_EventInterruptStatus_t;

typedef enum{
	I2C_ERROR_INTERRUPT_DISABLE,
	I2C_ERROR_INTERRUPT_ENABLE
}I2C_ErrorInterruptStatus_t;

typedef enum{
	I2C_OAR1_ONLY_RECOGNIZED,
	I2C_OAR1_OAR2_RECOGNIZED,
}I2C_DualAddressingMode_t;

typedef struct{
	I2C_DualAddressingMode_t DualAddressingMode;
	uint16 OwnAddress;
	uint16 DualAddress;
}I2C_SlaveDeviceAddress_t;

typedef enum{
	I2C_DIRECTION_WRITE,
	I2C_DIRECTION_READ
}I2C_DataDirection_t;

typedef struct{
	I2C_Mode_t I2C_Mode;
	uint32 I2C_Clock; // SM : up to 100k, FM : up to 400k
	I2C_AckStatus_t AckStatus;
	I2C_ClockStretchStatus_t ClockStretchStatus;
	I2C_GeneralCallStatus_t GeneralCallStatus;
	I2C_SMBusMode_t SMBusMode;
	I2C_MasterModeSelect_t MasterModeSelect;
	I2C_EventInterruptStatus_t EventInterruptStatus;
	I2C_ErrorInterruptStatus_t ErrorInterruptStatus;
	I2C_SlaveDeviceAddress_t  SlaveDeviceAddress;
	uint8 (*I2C_Slave_Transmit_Callback_Func)(void);
	void (*I2C_Slave_Receive_Callback_Func)(uint8 data);
	void (*I2C_Slave_Stop_Callback_Func)(void);
	void (*I2C_Error_Callback_Func)(uint8 error_code);
	void (*I2C_Error_Bus_Func)(void);
	void (*I2C_Error_ArbitrationLost_Func)(void);
	void (*I2C_Error_AcknowledgeFailure_Func)(void);
	void (*I2C_Error_OverrunUnderrun_Func)(void);
	void (*I2C_Error_PEC_Func)(void);
}I2C_Config_t;

/*
 * Bit 1 BUSY: Bus busy
		0: No communication on the bus
		1: Communication ongoing on the bus
		– Set by hardware on detection of SDA or SCL low
		– cleared by hardware on detection of a Stop condition.
		It indicates a communication in progress on the bus. This information is still updated when
		the interface is disabled (PE=0).
 */
typedef enum{
	I2C_BUS_IS_IDLE,
	I2C_BUS_IS_BUSY
}I2C_BusStatus_t;

/*
 * Bit 0 SB: Start bit (Master mode)
		0: No Start condition
		1: Start condition generated.
		– Set when a Start condition generated.
		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		hardware when PE=0
 */
typedef enum{
	I2C_START_IS_NOT_TRANSMITTED,
	I2C_START_IS_TRANSMITTED
}I2C_StartConditionTransmitted_t;

/*
 * Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		when PE=0.
		Address matched (Slave)
		0: Address mismatched or not received.
		1: Received address matched.
		– Set by hardware as soon as the received slave address matched with the OAR registers
		content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
		is recognized. (when enabled depending on configuration).
		Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
		SR1 then READ SR2) after ADDR is set. Refer to Figure 272.
		Address sent (Master)
		0: No end of address transmission
		1: End of address transmission
		– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
		– For 7-bit addressing, the bit is set after the ACK of the byte.
		Note: ADDR is not set after a NACK reception
 */
typedef enum{
	I2C_SLAVE_ADDRESS_IS_NOT_TRANSMITTED,
	I2C_SLAVE_ADDRESS_IS_TRANSMITTED
}I2C_IsSlaveAddressTransmitted_t;

/*
 * Bit 7 TxE: Data register empty (transmitters)
		0: Data register not empty
		1: Data register empty
		– Set when DR is empty in transmission. TxE is not set during address phase.
		– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		or when PE=0.
		TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
		BTF is set, as in both cases the data register is still empty.
 */
typedef enum{
	I2C_TRANSMIT_BUFFER_NOT_EMPTY,
	I2C_TRANSMIT_BUFFER_EMPTY
}I2C_TransmitBufferStatus_t;

/*
 * Bit 6 RxNE: Data register not empty (receivers)
		0: Data register empty
		1: Data register not empty
		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		– Cleared by software reading or writing the DR register or by hardware when PE=0.
		RxNE is not set in case of ARLO event.
		Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
 */
typedef enum{
	I2C_RECIEVE_BUFFER_EMPTY,
	I2C_RECIEVE_BUFFER_NOT_EMPTY
}I2C_IsRecieveBufferEmpty_t;

/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */


/* ================================================================ */
/* ============= APIs Supported by "MCAL I2C DRIVER"============= */
/* ================================================================ */

void MCAL_I2C_Init(I2C_t *I2Cx, I2C_Config_t *I2C_config);
void MCAL_I2C_Deinit(I2C_t *I2Cx, I2C_Config_t *I2C_config);

void MCAL_I2C_Set_GPIO_Pins(I2C_t *I2Cx);
void MCAL_I2C_Reset_GPIO_Pins(I2C_t *I2Cx);

void MCAL_I2C_Master_Transmit_Start(I2C_t *I2Cx);
void MCAL_I2C_Master_Transmit_RepeatedStart(I2C_t *I2Cx);
void MCAL_I2C_Master_Transmit_Stop(I2C_t *I2Cx);
void MCAL_I2C_Master_Transmit_Address(I2C_t *I2Cx, uint8 SlaveAddress, I2C_DataDirection_t dataDirection);

void MCAL_Transmit_Byte(I2C_t *I2Cx, uint8 byte);
uint8 MCAL_Recieve_With_ACK(I2C_t *I2Cx);
uint8 MCAL_Recieve_With_NACK(I2C_t *I2Cx);

void MCAL_I2C_Master_Transmit(I2C_t *I2Cx, uint8 SlaveAddress, uint8 *dataOut, uint8 length);
void MCAL_I2C_Master_Reieve(I2C_t *I2Cx, uint8 SlaveAddress, uint8 *dataIn, uint8 length);

void I2C_Slave_PollingTransmit(I2C_t *I2Cx, uint8 *dataOut, uint8 length);
void I2C_Slave_PollingReceive(I2C_t *I2Cx, uint8 *dataIn, uint8 length);

#endif /* INC_STM32F103X6_SPI_DRIVER_H_ */
