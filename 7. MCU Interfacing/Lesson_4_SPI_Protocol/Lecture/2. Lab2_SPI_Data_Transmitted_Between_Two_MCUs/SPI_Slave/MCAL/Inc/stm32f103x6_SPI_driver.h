/*
 * stm32f103x6_SPI_driver.h
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

typedef enum {
	SPI_MODE_SLAVE  = 0,   // Slave mode
    SPI_MODE_MASTER = 1    // Master mode

} SPI_mode_t;

typedef enum {
    SPI_DATASIZE_8BIT  = 0, // 8-bit data frame format
    SPI_DATASIZE_16BIT = 1  // 16-bit data frame format
} SPI_DataSize_t;

typedef enum {
    SPI_DFF_MSB_FIRST = 0,  // Data transmitted/received with MSB first
    SPI_DFF_LSB_FIRST = 1   // Data transmitted/received with LSB first
} SPI_DataFrameFormat_t;

typedef enum {
    SPI_BDM_2LINE_UNIDIR = 0, // Full duplex (2-line unidirectional)
    SPI_BDM_1LINE_BIDIR  = 1  // Simplex or half-duplex (1-line bidirectional)
} SPI_BidirectionalDataMode_t;

typedef enum {
    SPI_BDOE_DISABLE = 0, // Output disabled (receive-only mode)
    SPI_BDOE_ENABLE  = 1  // Output enabled (transmit mode)
} SPI_BidirectionalOutputEnable_t;

typedef enum {
    SPI_UNIDIR_RXONLY_DISABLE = 0, // Full-duplex mode
    SPI_UNIDIR_RXONLY_ENABLE  = 1  // Receive-only mode
} SPI_UnidirectionalReceiveOnly_t;

typedef enum {
    SPI_SSM_DISABLED = 0, // Hardware NSS management
    SPI_SSM_ENABLED  = 1  // Software NSS management
} SPI_SoftwareSlaveManagement_t;

typedef enum {
    SPI_CPOL_LOW  = 0, // Clock polarity low
    SPI_CPOL_HIGH = 1  // Clock polarity high
} SPI_ClockPriority_t;

typedef enum {
    SPI_CPHA_FIRST_EDGE  = 0, // Clock phase: data captured on the first edge
    SPI_CPHA_SECOND_EDGE = 1  // Clock phase: data captured on the second edge
} SPI_ClockPhase_t;

typedef enum {
    SPI_BAUDRATE_FPCLK_DIV_2   = 0, // fPCLK/2
    SPI_BAUDRATE_FPCLK_DIV_4   = 1, // fPCLK/4
    SPI_BAUDRATE_FPCLK_DIV_8   = 2, // fPCLK/8
    SPI_BAUDRATE_FPCLK_DIV_16  = 3, // fPCLK/16
    SPI_BAUDRATE_FPCLK_DIV_32  = 4, // fPCLK/32
    SPI_BAUDRATE_FPCLK_DIV_64  = 5, // fPCLK/64
    SPI_BAUDRATE_FPCLK_DIV_128 = 6, // fPCLK/128
    SPI_BAUDRATE_FPCLK_DIV_256 = 7  // fPCLK/256
} SPI_BaudrateControl_t;

typedef enum {
    SPI_CRC_DISABLED = 0, // CRC calculation disabled
    SPI_CRC_ENABLED  = 1  // CRC calculation enabled
} SPI_CRCEnable_t;

typedef enum {
    SPI_TXE_IRQ_DISABLED = 0, // TXE interrupt disabled (Data has been transmitted interrupt enable)
    SPI_TXE_IRQ_ENABLED  = 1  // TXE interrupt enabled
} SPI_TxBufferEmptyIRQ_t;

typedef enum {
    SPI_RXNE_IRQ_DISABLED = 0, // RXNE interrupt disabled
    SPI_RXNE_IRQ_ENABLED  = 1  // RXNE interrupt enabled (Data has been recieved interrupt enable)
} SPI_RxBufferEmptyIRQ_t;

typedef enum {
    SPI_SSOE_DISABLED = 0, // SS output disabled  (SS output is disabled in master mode and the cell can work in multimaster configuration)  => SS pin is input
    SPI_SSOE_ENABLED  = 1  // SS output enabled  => ss pin is output
} SPI_SSOE_State_t;

typedef struct {
	SPI_t                                           *SPIx;								 // SPI1/SPI2 Base Address
    SPI_mode_t 					 					mode;                                // Master or Slave mode
    SPI_DataSize_t								    dataSize;                        	 // Data frame size: 8-bit or 16-bit
    SPI_DataFrameFormat_t							frameFormat;              			 // MSB or LSB first
    SPI_BidirectionalDataMode_t  					bidirectionalMode;  				 // 1-line bidirectional or 2-line unidirectional
    SPI_BidirectionalOutputEnable_t 				bidiOutputEnable;					 // Transmit or receive-only in 1-line mode
    SPI_UnidirectionalReceiveOnly_t 				rxOnlyMode;     					 // Receive-only mode for unidirectional
    SPI_SoftwareSlaveManagement_t 					ssm;           					     // Hardware or software NSS management
    SPI_ClockPriority_t 							clockPolarity;            			 // CPOL: Clock polarity
    SPI_ClockPhase_t 								clockPhase;                 	     // CPHA: Clock phase
    SPI_BaudrateControl_t 							baudRate;               			 // Baud rate divider
    SPI_CRCEnable_t 								crcEnable;                  	     // Enable or disable CRC calculation
    uint16  										crcPolynomial;                       // CRC polynomial for CRC calculation
    SPI_TxBufferEmptyIRQ_t 							txeInterrupt;          				 // Enable or disable TXE interrupt
    SPI_RxBufferEmptyIRQ_t 							rxneInterrupt;         				 // Enable or disable RXNE interrupt
    SPI_SSOE_State_t 								ssoe;                        		 // SS output enable or disable
    void (*SPI_CallBackFun)(void);														 // SPI Callback Function
} SPI_Config_t;


/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */


/* ================================================================ */
/* ============= APIs Supported by "MCAL USART DRIVER"============= */
/* ================================================================ */

void MCAL_SPI_Init(SPI_Config_t *SPI_config);

void MCAL_SPI_Transmit(SPI_Config_t *SPI_config, uint16 data);
uint16 MCAL_SPI_Recieve(SPI_Config_t *SPI_config);
uint16 MCAL_SPI_Transmit_Recieve(SPI_Config_t *SPI_config, uint16 data);

void MCAL_SPI_Dinit(SPI_Config_t *SPI_config);


#endif /* INC_STM32F103X6_SPI_DRIVER_H_ */
