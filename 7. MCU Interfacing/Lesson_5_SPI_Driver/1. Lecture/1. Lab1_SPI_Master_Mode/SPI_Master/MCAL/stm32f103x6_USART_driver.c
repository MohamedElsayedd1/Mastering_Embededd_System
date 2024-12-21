/*
 * stm32f103x6_USART_driver.C
 *
 *  Created on: Dec 15, 2024
 *      Author: Mohamed ELsayed
 */

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_USART_driver.h"

/* ================================================================ */
/* ======================= Global Variables ======================= */
/* ================================================================ */
USART_Config_t* Global_USART_Config[3] = {NULL};

/* ================================================================ */
/* ======================== Static APIs =========================== */
/* ================================================================ */

/**
 * @Function    MCAL_USART_WaitForTc
 * @brief       Waits for the USART transmission to complete.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the USART instance.
 *
 * @Retval      None
 *
 * @Note        This function is static and intended for internal use only.
 *              It ensures that all data is transmitted before proceeding.
 */
static void MCAL_USART_WaitForTc(USART_Config_t *USART_Config){
	while (!(READ_BIT(USART_Config->USARTx->SR, 6)));
}

/**
 * @Function    MCAL_USART_SetBaudRate
 * @brief       Configures the baud rate for the USART peripheral.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure containing
 *                            the desired baud rate and configuration.
 *
 * @Retval      None
 *
 * @Note        This function is static and intended for internal use only.
 *              The calculation for the baud rate register depends on the clock frequency.
 */
static void MCAL_USART_SetBaudRate(USART_Config_t *USART_Config, uint32 F_CLK){
	/*
	     * USARTDIV = fCK / (16 * baud_rate)
	     * BRR[15:4] = Mantissa
	     * BRR[3:0] = Fraction
	 */
	uint32 USARTDIV = (F_CLK / (16UL * (USART_Config->baud_rate)));
	uint32 USARTDIV_MUL100 = ((F_CLK / (16UL * (USART_Config->baud_rate))) * 100);
	uint16 DIV_Mantissa = USARTDIV;                       // Mantissa part
	uint16 DIV_Mantissa_MUL100 = DIV_Mantissa * 100;
	uint8 DIV_Fraction = ((USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16) / 100;       // Function part

	USART_Config->USARTx->BRR = ((DIV_Mantissa << 4) | (DIV_Fraction & 0xF));
}

/**
 * @Function    MCAL_USART_GPIO_Set_Pins
 * @brief       Configures the GPIO pins for USART functionality (TX, RX, CTS, RTS).
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the GPIO pin configuration.
 *
 * @Retval      None
 *
 * @Note        This function is static and intended for internal use only.
 *              Ensure that the GPIO peripheral is properly initialized before calling this function.
 */
static void MCAL_USART_GPIO_Set_Pins(USART_Config_t *USART_Config) {
    GPIO_PinConfig_t pinConfig;

    if (USART_Config->USARTx == USART1) {
        // Configure Tx (PA9 or PB6)
        pinConfig.PinNum = GPIO_PIN9;  // Default: PA9
        pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
        pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
        MCAL_GPIO_Init(GPIOA, &pinConfig);

        // Configure Rx (PA10 or PB7)
        pinConfig.PinNum = GPIO_PIN10;  // Default: PA10
        pinConfig.PinMode = GPIO_INPUT;
        pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
        MCAL_GPIO_Init(GPIOA, &pinConfig);

        // Configure CTS (PA11) if enabled
        if (USART_Config->CTS_CTRL == USART_CTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN11;  // CTS: PA11
            pinConfig.PinMode = GPIO_INPUT;
            pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
            MCAL_GPIO_Init(GPIOA, &pinConfig);
        }

        // Configure RTS (PA12) if enabled
        if (USART_Config->RTS_CTRL == USART_RTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN12;  // RTS: PA12
            pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
            pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
            MCAL_GPIO_Init(GPIOA, &pinConfig);
        }
    }
    else if (USART_Config->USARTx == USART2) {
        // Configure Tx (PA2)
        pinConfig.PinNum = GPIO_PIN2;  // Tx: PA2
        pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
        pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
        MCAL_GPIO_Init(GPIOA, &pinConfig);

        // Configure Rx (PA3)
        pinConfig.PinNum = GPIO_PIN3;  // Rx: PA3
        pinConfig.PinMode = GPIO_INPUT;
        pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
        MCAL_GPIO_Init(GPIOA, &pinConfig);

        // Configure CTS (PA0) if enabled
        if (USART_Config->CTS_CTRL == USART_CTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN0;  // CTS: PA0
            pinConfig.PinMode = GPIO_INPUT;
            pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
            MCAL_GPIO_Init(GPIOA, &pinConfig);
        }

        // Configure RTS (PA1) if enabled
        if (USART_Config->RTS_CTRL == USART_RTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN1;  // RTS: PA1
            pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
            pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
            MCAL_GPIO_Init(GPIOA, &pinConfig);
        }
    }
    else if (USART_Config->USARTx == USART3) {
        // Configure Tx (PB10)
        pinConfig.PinNum = GPIO_PIN10;  // Tx: PB10
        pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
        pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
        MCAL_GPIO_Init(GPIOB, &pinConfig);

        // Configure Rx (PB11)
        pinConfig.PinNum = GPIO_PIN11;  // Rx: PB11
        pinConfig.PinMode = GPIO_INPUT;
        pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
        MCAL_GPIO_Init(GPIOB, &pinConfig);

        // Configure CTS (PB13) if enabled
        if (USART_Config->CTS_CTRL == USART_CTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN13;  // CTS: PB13
            pinConfig.PinMode = GPIO_INPUT;
            pinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT;
            MCAL_GPIO_Init(GPIOB, &pinConfig);
        }

        // Configure RTS (PB14) if enabled
        if (USART_Config->RTS_CTRL == USART_RTS_ENABLED) {
            pinConfig.PinNum = GPIO_PIN14;  // RTS: PB14
            pinConfig.PinMode = GPIO_OUTPUT_10MHZ;
            pinConfig.PinCNF = GPIO_CNF_AF_PUSH_PULL_OUTPUT;
            MCAL_GPIO_Init(GPIOB, &pinConfig);
        }
    }
}



/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */


/**
 * @Function    MCAL_USART_Init
 * @brief       Initializes the USART peripheral with the specified configuration.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure containing
 *                            the configuration settings (e.g., baud rate, parity, etc.).
 *
 * @Retval      None
 *
 * @Note        This function must be called before using any USART transmit or receive APIs.
 */
void MCAL_USART_Init(USART_Config_t *USART_Config){
	uint32 F_CLK;

	// Enable the clock for configured USART (1, 2, 3)
	if(USART_Config->USARTx == USART1){
		USART1_CLK_EN();
		// PCLK2 for USART1
		Global_USART_Config[0] = USART_Config;
		F_CLK = MCAL_RCC_GetPCLK2_Freq();
	}
	else if(USART_Config->USARTx == USART2){
		USART2_CLK_EN();
		// PCLK1 for USART2
		F_CLK = MCAL_RCC_GetPCLK1_Freq();
		Global_USART_Config[1] = USART_Config;
	}
	else if(USART_Config->USARTx == USART3){
		USART3_CLK_EN();
		// PCLK1 for USART3
		F_CLK = MCAL_RCC_GetPCLK1_Freq();
		Global_USART_Config[2] = USART_Config;
	}

	// Configure the GPIO pins for Tx, Rx, CTS, RTS
	MCAL_USART_GPIO_Set_Pins(USART_Config);

	// Enable the USART by writing the UE bit in USART_CR1 register to 1
	SET_BIT(USART_Config->USARTx->CR1, 13);

	// Disable/Enable TX/RX
	if(USART_Config->TxMode == USART_TX_ENABLED)
		SET_BIT(USART_Config->USARTx->CR1, 3);
	if(USART_Config->TxMode == USART_RX_ENABLED)
		SET_BIT(USART_Config->USARTx->CR1, 2);

	// Set the Word Length
	if(USART_Config->wordLength == USART_9_BIT_WORD_LENGTH)
		SET_BIT(USART_Config->USARTx->CR1, 12);   // 9 bit data
	else
		CLEAR_BIT(USART_Config->USARTx->CR1, 12); // 8 bit data

	// Enable/Disable Parity bit
	if(USART_Config->parityMode == USART_ENABLED_PARITY)
		SET_BIT(USART_Config->USARTx->CR1, 10);    // Enable Parity
	else
		CLEAR_BIT(USART_Config->USARTx->CR1, 10);  // Disable Parity

	// Enable/Disable Hardware Flow Control (CTS, RTS)
	if(USART_Config->CTS_CTRL == USART_CTS_ENABLED)
		SET_BIT(USART_Config->USARTx->CR3, 9);    // Enable CTS Pin
	if(USART_Config->RTS_CTRL == USART_RTS_ENABLED)
		SET_BIT(USART_Config->USARTx->CR3, 8);  // Enable RTS Pin

	// Configure the number of stop bits
	USART_Config->USARTx->CR2 |= (USART_Config->stopBits << 12);

	// Configure the BaudRate
	MCAL_USART_SetBaudRate(USART_Config, F_CLK);

	// Enable/Disable Interrupt
	if((USART_Config->Tx_Interrupt_Enable == USART_TX_INTERRUPT_ENABLED) || (USART_Config->Rx_Interrupt_Enable == USART_RX_INTERRUPT_ENABLED)){
		// Enable NVIC for USARTx IRQ
		if(USART_Config->USARTx == USART1){
			NVIC_IRQ_ENABLE(USART1_IRQ);
		}
		else if(USART_Config->USARTx == USART2){
			NVIC_IRQ_ENABLE(USART2_IRQ);
		}
		else if(USART_Config->USARTx == USART3){
			NVIC_IRQ_ENABLE(USART3_IRQ);
		}

		// Enable Tx/Rx Interrupt Based on configuration
		if(USART_Config->Tx_Interrupt_Enable == USART_TX_INTERRUPT_ENABLED)
			SET_BIT(USART_Config->USARTx->CR1, 6);    // TCIE: Transmission complete interrupt enable
		if(USART_Config->Rx_Interrupt_Enable == USART_RX_INTERRUPT_ENABLED)
			SET_BIT(USART_Config->USARTx->CR1, 5);    // Bit 5 RXNEIE: RXNE interrupt enable
	}
}

/**
 * @Function    MCAL_USART_Deinit
 * @brief       Deinitializes the USART peripheral and resets all configurations.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the USART instance.
 *
 * @Retval      None
 *
 * @Note        This function disables the USART peripheral and resets all associated settings.
 */
void MCAL_USART_Deinit(USART_Config_t *USART_Config){
	// Reset the USART (1, 2, 3), Disable Interrupts
	if(USART_Config->USARTx == USART1){
		USART1_CLK_RST();
		NVIC_IRQ_DISABLE(USART1_IRQ);
	}
	else if(USART_Config->USARTx == USART2){
		USART2_CLK_RST();
		NVIC_IRQ_DISABLE(USART2_IRQ);
	}
	else if(USART_Config->USARTx == USART3){
		USART3_CLK_RST();
		NVIC_IRQ_DISABLE(USART3_IRQ);
	}
}

/**
 * @Function    MCAL_USART_TransmitByte
 * @brief       Transmits a single byte over the USART peripheral.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the USART instance.
 *
 * @Retval      None
 *
 * @Note        Ensure that the USART peripheral is initialized before calling this function.
 */
void MCAL_USART_TransmitByte(USART_Config_t *USART_Config, uint16 data){
	// Wait until the Transmit Data Register (TXE) is empty
	while (!(READ_BIT(USART_Config->USARTx->SR, 7)));

	// Load the data into the Data Register (DR) to start transmission
	USART_Config->USARTx->DR = data;

	// Optionally wait for Transmission Complete (TC) if required
	// (e.g., if this is the last byte of the transmission)
	MCAL_USART_WaitForTc(USART_Config);
}

/**
 * @Function    MCAL_USART_TransmitString
 * @brief       Transmits a string of characters over the USART peripheral.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the USART instance.
 *
 * @Retval      None
 *
 * @Note        The string must be null-terminated (`\0`) for proper transmission.
 */
void MCAL_USART_TransmitString(USART_Config_t *USART_Config, uint8 *str){
	while(*str){
		MCAL_USART_TransmitByte(USART_Config, *str++);
	}
}

/**
 * @Function    MCAL_USART_RecieveByte
 * @brief       Receives a single byte over the USART peripheral.
 *
 * @Param[in]   USART_Config  Pointer to a USART_Config_t structure specifying the USART instance.
 *
 * @Retval      None
 *
 * @Note        Ensure that the USART peripheral is initialized before calling this function.
 */
uint16 MCAL_USART_RecieveByte(USART_Config_t *USART_Config){
    uint16 Received;

    // Wait until RXNE (Read Data Register Not Empty) flag is set
    while (!(READ_BIT(USART_Config->USARTx->SR, 5)));

    // Check if Parity is enabled
    if (USART_Config->parityMode == USART_ENABLED_PARITY) {
        if (USART_Config->wordLength == USART_9_BIT_WORD_LENGTH) {
            // Parity enabled, 9-bit data (upper bit might contain parity info)
            Received = (uint16)(USART_Config->USARTx->DR & 0xFF);
        } else {
            // Parity enabled, 8-bit data (parity occupies the 9th bit, so mask to 7 bits)
            Received = (uint16)(USART_Config->USARTx->DR & 0x7F);
        }
    } else {
        // Parity disabled
        if (USART_Config->wordLength == USART_9_BIT_WORD_LENGTH) {
            // Parity disabled, full 9-bit data
            Received = (uint16)(USART_Config->USARTx->DR);
        } else {
            // Parity disabled, 8-bit data
            Received = (uint16)(USART_Config->USARTx->DR & 0xFF);
        }
    }

    return Received;
}


/* ================================================================ */
/* ============================= ISR ============================== */
/* ================================================================ */

void USART1_IRQHandler(void){
	Global_USART_Config[0]->USARTx_CallBackFunction();
}

void USART2_IRQHandler(void){
	Global_USART_Config[1]->USARTx_CallBackFunction();
}

void USART3_IRQHandler(void){
	Global_USART_Config[2]->USARTx_CallBackFunction();
}

