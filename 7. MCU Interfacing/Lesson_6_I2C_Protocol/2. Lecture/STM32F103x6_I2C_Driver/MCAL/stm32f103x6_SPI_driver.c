/*
 * stm32f103x6_SPI_driver.c
 *
 *  Created on: Dec 19, 2024
 *      Author: Mohamed Elsayed
 */

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_SPI_driver.h"

/* ================================================================ */
/* ======================= Global Variables ======================= */
/* ================================================================ */
void (*SPI_CallBackFunction[2])(void) = {NULL, NULL};


/* ================================================================ */
/* ======================== Static APIs =========================== */
/* ================================================================ */

static void MCAL_SPI_Set_GPIO_Pins(SPI_Config_t *SPI_config){
	GPIO_PinConfig_t PinCfg;
	if(SPI_config->SPIx == SPI1){
		// SPI1_NSS : PA4
		// SPI1_SCK : PA5
		// SPI1_MISO : PA6
		// SPI1_MOSI : PA7
		if(SPI_config->mode == SPI_MODE_SLAVE){
			// Set MISO as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN6;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			// Set MOSI as input floating / Input pull-up
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN7;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			// Set SPI1_SCK as input floating
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN5;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			if(SPI_config->ssm == SPI_SSM_DISABLED){  // Hardware NSS management
				// Set SPIx_NSS as Input floating
				PinCfg.PinMode = GPIO_INPUT;
				PinCfg.PinNum = GPIO_PIN4;
				PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
		}
		else if(SPI_config->mode == SPI_MODE_MASTER){
			// Set MISO as Input floating
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN6;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			// Set MOSI as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN7;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			// Set SPI1_SCK as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN5;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			if(SPI_config->ssm == SPI_SSM_DISABLED){  // Hardware NSS management
				if(SPI_config->ssoe == SPI_SSOE_DISABLED){
					// SS output disabled  (SS output is disabled in master mode and the cell can work in multimaster configuration)  => SPIx_NSS pin is Input floating
					PinCfg.PinMode = GPIO_INPUT;
					PinCfg.PinNum = GPIO_PIN4;
					PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
					MCAL_GPIO_Init(GPIOA, &PinCfg);
				}
				else if(SPI_config->ssoe == SPI_SSOE_ENABLED){
					// SS output enabled  => SPIx_NSS pin is Alternate function push-pull
					PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
					PinCfg.PinNum = GPIO_PIN4;
					PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
					MCAL_GPIO_Init(GPIOA, &PinCfg);
				}
			}
		}
	}
	else if(SPI_config->SPIx == SPI2){
		// SPI1_NSS : PB12
		// SPI1_SCK : PB13
		// SPI1_MISO : PB14
		// SPI1_MOSI : PB15
		if(SPI_config->mode == SPI_MODE_SLAVE){
			// Set MISO as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN14;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			// Set MOSI as input floating / Input pull-up
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN15;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			// Set SPI1_SCK as input floating
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN13;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			if(SPI_config->ssm == SPI_SSM_DISABLED){  // Hardware NSS management
				// Set SPIx_NSS as Input floating
				PinCfg.PinMode = GPIO_INPUT;
				PinCfg.PinNum = GPIO_PIN12;
				PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
		}
		else if(SPI_config->mode == SPI_MODE_MASTER){
			// Set MISO as Input floating
			PinCfg.PinMode = GPIO_INPUT;
			PinCfg.PinNum = GPIO_PIN14;
			PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			// Set MOSI as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN15;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			// Set SPI1_SCK as Alternate function push-pull
			PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
			PinCfg.PinNum = GPIO_PIN13;
			PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			if(SPI_config->ssm == SPI_SSM_DISABLED){  // Hardware NSS management
				if(SPI_config->ssoe == SPI_SSOE_DISABLED){
					// SS output disabled  (SS output is disabled in master mode and the cell can work in multimaster configuration)  => SPIx_NSS pin is Input floating
					PinCfg.PinMode = GPIO_INPUT;
					PinCfg.PinNum = GPIO_PIN12;
					PinCfg.PinCNF = GPIO_CNF_FLOATING_INPUT;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
				}
				else if(SPI_config->ssoe == SPI_SSOE_ENABLED){
					// SS output enabled  => SPIx_NSS pin is Alternate function push-pull
					PinCfg.PinMode = GPIO_OUTPUT_10MHZ;
					PinCfg.PinNum = GPIO_PIN12;
					PinCfg.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
				}
			}
		}
	}
}

static void MCAL_SPI_SetCallBackFunction(SPI_Config_t *SPI_config){
	// Set the callback function for both SPI1/SPI2
	if(SPI_config->SPIx == SPI1){
		SPI_CallBackFunction[0] = SPI_config->SPI_CallBackFun;
	}
	else if(SPI_config->SPIx == SPI2){
		SPI_CallBackFunction[1] = SPI_config->SPI_CallBackFun;
	}
}

static void MCAL_SPI_Enable_Global_Interrupt(SPI_Config_t *SPI_config){
	// Enable the clock for SPI1/SPI2
	if(SPI_config->SPIx == SPI1){
		NVIC_IRQ_ENABLE(SPI1_IRQ);
	}
	else if(SPI_config->SPIx == SPI2){
		NVIC_IRQ_ENABLE(SPI2_IRQ);
	}
}

static void MCAL_SPI_Disable_Global_Interrupt(SPI_Config_t *SPI_config){
	// Disable the clock for SPI1/SPI2
	if(SPI_config->SPIx == SPI1){
		NVIC_IRQ_DISABLE(SPI1_IRQ);
	}
	else if(SPI_config->SPIx == SPI2){
		NVIC_IRQ_DISABLE(SPI2_IRQ);
	}
}


/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

void MCAL_SPI_Init(SPI_Config_t *SPI_config){
	// Enable the clock for SPI1/SPI2
	if(SPI_config->SPIx == SPI1){
		SPI1_CLK_EN();

	}
	else if(SPI_config->SPIx == SPI2){
		SPI1_CLK_EN();
	}

	/*
		Bit 2 MSTR: Master selection
			0: Slave configuration
			1: Master configuration
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->mode << 2);

	/*
	    Bit 15 BIDIMODE: Bidirectional data mode enable
			0: 2-line unidirectional data mode selected
			1: 1-line bidirectional data mode selected
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->bidirectionalMode << 15);

	/*
		Bit 14 BIDIOE: Output enable in bidirectional mode
			This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
			0: Output disabled (receive-only mode)
			1: Output enabled (transmit-only mode)
	 */
	if(SPI_config->bidirectionalMode == SPI_BDM_1LINE_BIDIR)
		SPI_config->SPIx->CR1 |= (SPI_config->bidiOutputEnable << 14);

	/*
		Bit 13 CRCEN: Hardware CRC calculation enable
			0: CRC calculation disabled
			1: CRC calculation enabled
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->crcEnable << 13);

	/*
		Bit 13 CRCEN: Hardware CRC calculation enable
			0: CRC calculation disabled
			1: CRC calculation enabled
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->crcEnable << 13);

	/*
		Bit 11 DFF: Data frame format
			0: 8-bit data frame format is selected for transmission/reception
			1: 16-bit data frame format is selected for transmission/reception
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->dataSize << 11);

	/*
		Bit 10 RXONLY: Receive only
			This bit combined with the BIDImode bit selects the direction of transfer in 2-line
			unidirectional mode. This bit is also useful in a multislave system in which this particular
			slave is not accessed, the output from the accessed slave is not corrupted.
			0: Full duplex (Transmit and receive)
			1: Output disabled (Receive-only mode)
	 */
	if(SPI_config->bidirectionalMode == SPI_BDM_2LINE_UNIDIR)  // Full duplex (2-line unidirectional)
		SPI_config->SPIx->CR1 |= (SPI_config->rxOnlyMode << 11);           // Receive-only mode for unidirectional

	/*
		Bit 9 SSM: Software slave management
			When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
			0: Software slave management disabled
			1: Software slave management enabled
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->ssm << 9);          				// Hardware or software NSS management

	/*
		Bit 8 SSI: Internal slave select
			This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
			NSS pin and the IO value of the NSS pin is ignored.
	 */
	if(SPI_config->ssm == SPI_SSM_ENABLED){
		// Software NSS management
		if(SPI_config->mode == SPI_MODE_MASTER){
			// Master mode => Set SSI pin HIGH
			SET_BIT(SPI_config->SPIx->CR1, 8);
		}
		else if(SPI_config->mode == SPI_MODE_SLAVE){
			// Slve mode => Set SSI pin LOW
			CLEAR_BIT(SPI_config->SPIx->CR1, 8);
		}
	}

	/*
		Bit 7 LSBFIRST: Frame format
			0: MSB transmitted first
			1: LSB transmitted first
	 */
	SPI_config->SPIx->CR1 |= (SPI_config->frameFormat << 7);

	/*
		Bits 5:3 BR[2:0]: Baud rate control
			000: fPCLK/2
			001: fPCLK/4
			010: fPCLK/8
			011: fPCLK/16
			100: fPCLK/32
			101: fPCLK/64
			110: fPCLK/128
			111: fPCLK/256
	 */
	if(SPI_config->mode == SPI_MODE_MASTER){    // Master mode
		SPI_config->SPIx->CR1 &= ~(0b111 << 3);
		SPI_config->SPIx->CR1 |= ((SPI_config->baudRate & 0x7) << 3);
	}

	/*
		Bit 2 SSOE: SS output enable
			0: SS output is disabled in master mode and the cell can work in multimaster configuration
			1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
			in a multimaster environment.
	 */
	SPI_config->SPIx->CR2 |= (SPI_config->ssoe << 2);

	/*
		Bit 7 TXEIE: Tx buffer empty interrupt enable
			0: TXE interrupt masked
			1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
	 */
	if(SPI_config->txeInterrupt == SPI_TXE_IRQ_ENABLED){
		SET_BIT(SPI_config->SPIx->CR2, 7);
		// Enable Global Interrupt
		MCAL_SPI_Enable_Global_Interrupt(SPI_config);
	}

	/*
		Bit 6 RXNEIE: RX buffer not empty interrupt enable
			0: RXNE interrupt masked
			1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is.
	 */
	if(SPI_config->rxneInterrupt == SPI_RXNE_IRQ_ENABLED){
		SET_BIT(SPI_config->SPIx->CR2, 6);
		// Enable Global Interrupt
		MCAL_SPI_Enable_Global_Interrupt(SPI_config);
	}

	// Set the function callback
	MCAL_SPI_SetCallBackFunction(SPI_config);

	// Set GPIO pins for SPI
	MCAL_SPI_Set_GPIO_Pins(SPI_config);

	// Enable SPI1/SPI2
	/*
	 	 Bit 6 SPE: SPI enable
			0: Peripheral disabled
			1: Peripheral enabled
	 */
	SET_BIT(SPI_config->SPIx->CR1, 6);
}


void MCAL_SPI_Transmit(SPI_Config_t *SPI_config, uint16 data){
	/*
	 	 Bit 1 TXE: Transmit buffer empty
			0: Tx buffer not empty
			1: Tx buffer empty
	 */
	while(!(READ_BIT(SPI_config->SPIx->SR, 1)));
	SPI_config->SPIx->DR = data;
}

uint16 MCAL_SPI_Recieve(SPI_Config_t *SPI_config){
	uint16 RecievedData;
	/*
		 Bit 0 RXNE: Receive buffer not empty
			0: Rx buffer empty
			1: Rx buffer not empty
	 */
	while(!(READ_BIT(SPI_config->SPIx->SR, 0)));
	RecievedData = SPI_config->SPIx->DR;
	return RecievedData;
}

uint16 MCAL_SPI_Transmit_Recieve(SPI_Config_t *SPI_config, uint16 data){
	uint16 RecievedData;
	MCAL_SPI_Transmit(SPI_config, data);
	RecievedData = MCAL_SPI_Recieve(SPI_config);
	return RecievedData;
}

void MCAL_SPI_Dinit(SPI_Config_t *SPI_config){
	// Disable Global Interrupt
	MCAL_SPI_Disable_Global_Interrupt(SPI_config);
	// Reset Peripheral Registers
	if(SPI_config->SPIx == SPI1){
		SPI1_CLK_RST();
	}
	else if(SPI_config->SPIx == SPI2){
		SPI2_CLK_RST();
	}
}

/* ================================================================ */
/* ============================= ISR ============================== */
/* ================================================================ */

void SPI1_IRQHandler(void){
	SPI_CallBackFunction[0]();
}

void SPI2_IRQHandler(void){
	SPI_CallBackFunction[1]();
}
