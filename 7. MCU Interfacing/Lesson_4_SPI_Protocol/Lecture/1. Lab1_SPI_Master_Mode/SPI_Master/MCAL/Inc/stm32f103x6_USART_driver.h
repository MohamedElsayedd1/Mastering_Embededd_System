/*
 * stm32f103x6_USART_driver.h
 *
 *  Created on: Dec 15, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_USART_DRIVER_H_
#define INC_STM32F103X6_USART_DRIVER_H_



/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6.h"
#include "stm32f103x6_RCC_driver.h"
#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6_USART_driver.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef enum{
	USART_8_BIT_WORD_LENGTH,
	USART_9_BIT_WORD_LENGTH
}USART_WordBit_Length_t;

typedef enum{
	USART_DISABLED_PARITY,
	USART_ENABLED_PARITY
}USART_ParityMode_t;

typedef enum{
	USART_1_STOP_BITS,
	USART_HALF_STOP_BITS,
	USART_2_STOP_BITS,
	USART_ONE_AND_HALF_STOP_BITS
}USART_StopBits_t;

typedef enum{
	USART_EVEN_PARITY,
	USART_ODD_PARITY
}USART_ParitySelect_t;

typedef enum{
	USART_TX_DISABLED,
	USART_TX_ENABLED
}USART_TxMode_t;

typedef enum{
	USART_RX_DISABLED,
	USART_RX_ENABLED
}USART_RxMode_t;

typedef enum{
	USART_TX_INTERRUPT_DISABLED,
	USART_TX_INTERRUPT_ENABLED
}USART_Tx_Interrupt_Enable_t;

typedef enum{
	USART_RX_INTERRUPT_DISABLED,
	USART_RX_INTERRUPT_ENABLED
}USART_Rx_Interrupt_Enable_t;

typedef enum{
	USART_CTS_DISABLED,
	USART_CTS_ENABLED
}USART_CTS_FlowControl_t;

typedef enum{
	USART_RTS_DISABLED,
	USART_RTS_ENABLED
}USART_RTS_FlowControl_t;


typedef struct{
	USART_t *USARTx;
	USART_WordBit_Length_t 				wordLength;
	USART_ParityMode_t    				parityMode;
	USART_ParitySelect_t				paritySelect;
	USART_StopBits_t    				stopBits;
	USART_TxMode_t						TxMode;
	USART_RxMode_t						RxMode;
	USART_Tx_Interrupt_Enable_t         Tx_Interrupt_Enable;
	USART_Rx_Interrupt_Enable_t         Rx_Interrupt_Enable;
	USART_CTS_FlowControl_t 			CTS_CTRL;
	USART_RTS_FlowControl_t   			RTS_CTRL;
	uint32								baud_rate;
	void (*USARTx_CallBackFunction)();
}USART_Config_t;


/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */


/* ================================================================ */
/* ============= APIs Supported by "MCAL USART DRIVER"============= */
/* ================================================================ */

void MCAL_USART_Init(USART_Config_t *USART_Config);
void MCAL_USART_Deinit(USART_Config_t *USART_Config);


void MCAL_USART_TransmitByte(USART_Config_t *USART_Config, uint16 data);
void MCAL_USART_TransmitString(USART_Config_t *USART_Config, uint8 *str);

uint16 MCAL_USART_RecieveByte(USART_Config_t *USART_Config);

#endif /* INC_STM32F103X6_USART_DRIVER_H_ */
