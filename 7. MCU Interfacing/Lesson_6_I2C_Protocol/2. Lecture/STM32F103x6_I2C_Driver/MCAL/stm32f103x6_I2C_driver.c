/*
 * stm32f103x6_I2C_driver.c
 *
 *  Created on: Dec 19, 2024
 *      Author: Mohamed Elsayed
 */

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_I2C_driver.h"

/* ================================================================ */
/* ======================= Global Variables ======================= */
/* ================================================================ */

static uint8 (*I2C_Slave_Transmit_Callback)(void);
static void (*I2C_Slave_Receive_Callback)(uint8 data);
static void (*I2C_Slave_Stop_Callback)(void);
static void (*I2C_Error_Callback)(uint8 error_code);
static void (*I2C_Error_Bus)(void);
static void (*I2C_Error_ArbitrationLost)(void);
static void (*I2C_Error_AcknowledgeFailure)(void);
static void (*I2C_Error_OverrunUnderrun)(void);
static void (*I2C_Error_PEC)(void);

/* ================================================================ */
/* ======================== Static APIs =========================== */
/* ================================================================ */

static I2C_BusStatus_t I2C_IsBusBusy(I2C_t *I2Cx){
	/*
	 * Bit 1 BUSY: Bus busy
		0: No communication on the bus
		1: Communication ongoing on the bus
	 */
	I2C_BusStatus_t flag = READ_BIT(I2Cx->SR2, 1);
	return flag;
}

static I2C_StartConditionTransmitted_t I2C_IsStartTransmitted(I2C_t *I2Cx){
	/*
	 * Bit 0 SB: Start bit (Master mode)
			0: No Start condition
			1: Start condition generated.
			– Set when a Start condition generated.
			– Cleared by software by reading the SR1 register followed by writing the DR register, or by
			hardware when PE=0
	 */
	I2C_StartConditionTransmitted_t flag = READ_BIT(I2Cx->SR1, 0);
	return flag;
}

static I2C_IsSlaveAddressTransmitted_t I2C_IsSlaveAddressTransmitted(I2C_t *I2Cx){
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
	I2C_IsSlaveAddressTransmitted_t flag = READ_BIT(I2Cx->SR1, 1);
	return flag;
}


static I2C_TransmitBufferStatus_t I2C_IsTransmitBufferEmpty(I2C_t *I2Cx) {
    /*
     * Bit 7 TXE: Data register empty (transmitters)
        0: Data register not empty
        1: Data register empty
     */
    return (I2C_TransmitBufferStatus_t)READ_BIT(I2Cx->SR1, 7); // Read TXE flag in SR1 register
}

static I2C_IsRecieveBufferEmpty_t I2C_IsRecieveBufferEmpty(I2C_t *I2Cx){
	/*
	 * Bit 6 RxNE: Data register not empty (receivers)
			0: Data register empty
			1: Data register not empty
			– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
			– Cleared by software reading or writing the DR register or by hardware when PE=0.
			RxNE is not set in case of ARLO event.
			Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
	 */
    return (I2C_IsRecieveBufferEmpty_t)READ_BIT(I2Cx->SR1, 6);
}

/* ================================================================ */
/* ======================== Public APIs =========================== */
/* ================================================================ */

void MCAL_I2C_Init(I2C_t *I2Cx, I2C_Config_t *I2C_config){
	// Enable GPIOB and I2C clock
	GPIOB_CLK_EN();
	if(I2Cx == I2C1){
		I2C1_CLK_EN();
	}
	else if(I2Cx == I2C2){
		I2C2_CLK_EN();
	}
	else{
		return;
	}

	// Set GPIO Pins
	MCAL_I2C_Set_GPIO_Pins(I2Cx);

	// Program input clock in CR2
	// Bits 5:0 FREQ[5:0]: Peripheral clock frequency
	uint32 Pclk1 = MCAL_RCC_GetPCLK1_Freq();
	I2Cx->CR2 &= ~(0b111111 << 0); // Clear FREQ[5:0] first
	I2Cx->CR2 |= ((Pclk1 / 1000000UL) << 0);

	// Configure the input clock
	uint32 ccr = (Pclk1 / (I2C_config->I2C_Clock << 1));
	CLEAR_BIT(I2Cx->CR2, 14); // Bit 14 DUTY: Fm mode duty cycle
	/*
	 * Bit 15 F/S: I2C master mode selection
		0: Sm mode I2C
		1: Fm mode I2C
	 */
	I2Cx->CR2 |= (I2C_config->MasterModeSelect << 15);
	I2Cx->CCR &= ~(0xFFF << 0); // Clear CCR[11:0]
	I2Cx->CCR |= (ccr << 0);

	// Configure TRISE
	I2Cx->TRISE = (I2C_config->MasterModeSelect == I2C_SM_MODE) ? (Pclk1 / 1000000) + 1 : ((Pclk1 / 3000000) + 1);

	// Configure Interrupt
	// Slave : Use interrupt
	// Master : Use Polling
	if(I2C_config->I2C_Mode == I2C_SLAVE_MODE){
		// Enable Interrupt Masks
		SET_BIT(I2Cx->CR2, 10);  // Bit 10 ITBUFEN: Buffer interrupt enable
		SET_BIT(I2Cx->CR2, 9);  // ITEVTEN: Event interrupt enable
		SET_BIT(I2Cx->CR2, 8);  // ITERREN: Error interrupt enable
		if(I2Cx == I2C1){
			NVIC_IRQ_0_31_ENABLE(I2C1_EVENT_IRQ);
			NVIC_IRQ_32_63_ENABLE(I2C1_ERROR_IRQ);
		}
		else if(I2Cx == I2C2){
			NVIC_IRQ_0_31_ENABLE(I2C2_EVENT_IRQ);
			NVIC_IRQ_32_63_ENABLE(I2C2_ERROR_IRQ);
		}
		else{
			return;
		}
		// Set Call-Back Functions
		I2C_Slave_Transmit_Callback = I2C_config->I2C_Slave_Transmit_Callback_Func;
		I2C_Slave_Receive_Callback = I2C_config->I2C_Slave_Receive_Callback_Func;
		I2C_Slave_Stop_Callback = I2C_config->I2C_Slave_Stop_Callback_Func;
		I2C_Error_Callback = I2C_config->I2C_Error_Callback_Func;
		I2C_Error_Bus = I2C_config->I2C_Error_Bus_Func;
		I2C_Error_ArbitrationLost = I2C_config->I2C_Error_ArbitrationLost_Func;
		I2C_Error_AcknowledgeFailure = I2C_config->I2C_Error_AcknowledgeFailure_Func;
		I2C_Error_OverrunUnderrun = I2C_config->I2C_Error_OverrunUnderrun_Func;
		I2C_Error_PEC = I2C_config->I2C_Error_PEC_Func;
	}

	// Configure acknowledgment and own address
	I2Cx->CR1 |= (I2C_config->AckStatus << 10); // Bit 10 ACK: Acknowledge enable

	// Configure clock stretching
	I2Cx->CR1 |= (I2C_config->ClockStretchStatus << 7); // Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)

	// Configure General Call
	I2Cx->CR1 |= (I2C_config->GeneralCallStatus << 6); // Bit 6 ENGC: General call enable

	// Configure own address
	CLEAR_BIT(I2Cx->CR1, 0); // Bit 0 PE: Peripheral enable
	I2Cx->OAR2 |= (I2C_config->SlaveDeviceAddress.DualAddressingMode << 0); // Bit 0 ENDUAL: Dual addressing mode enable
	I2Cx->OAR1 = (1 << 14) | (I2C_config->SlaveDeviceAddress.OwnAddress << 1);
	if(I2C_config->SlaveDeviceAddress.DualAddressingMode == I2C_OAR1_OAR2_RECOGNIZED){
		I2Cx->OAR2 = (I2C_config->SlaveDeviceAddress.DualAddress << 1);
	}

	 // Enable I2C
	 I2Cx->CR1 |= (1 << 0); // Bit 0 PE: Peripheral enable
}

void MCAL_I2C_Reset_GPIO_Pins(I2C_t *I2Cx) {
    GPIO_PinConfig_t PinConfig;
    PinConfig.PinCNF = GPIO_CNF_FLOATING_INPUT; // Reset to default input mode
    PinConfig.PinMode = GPIO_INPUT;

    if (I2Cx == I2C1) {
        // PB6 (SCL) and PB7 (SDA) for I2C1
        PinConfig.PinNum = GPIO_PIN6;
        MCAL_GPIO_Init(GPIOB, &PinConfig);
        PinConfig.PinNum = GPIO_PIN7;
        MCAL_GPIO_Init(GPIOB, &PinConfig);
    } else if (I2Cx == I2C2) {
        // PB10 (SCL) and PB11 (SDA) for I2C2
        PinConfig.PinNum = GPIO_PIN10;
        MCAL_GPIO_Init(GPIOB, &PinConfig);
        PinConfig.PinNum = GPIO_PIN11;
        MCAL_GPIO_Init(GPIOB, &PinConfig);
    } else {
        return; // Invalid I2C peripheral
    }
}

void MCAL_I2C_Deinit(I2C_t *I2Cx, I2C_Config_t *I2C_config){
	// Disable I2C peripheral
	CLEAR_BIT(I2Cx->CR1, 0); // Bit 0 PE: Disable peripheral
	// Disable Interrupt Masks
	CLEAR_BIT(I2Cx->CR2, 10);  // Bit 10 ITBUFEN: Buffer interrupt enable
	CLEAR_BIT(I2Cx->CR2, 9);  // ITEVTEN: Event interrupt enable
	CLEAR_BIT(I2Cx->CR2, 8);  // ITERREN: Error interrupt enable
	if(I2Cx == I2C1){
		I2C1_CLK_RST();
		NVIC_IRQ_0_31_DISABLE(I2C1_EVENT_IRQ);
		NVIC_IRQ_32_63_DISABLE(I2C1_ERROR_IRQ);
	}
	else if(I2Cx == I2C2){
		I2C2_CLK_RST();
		NVIC_IRQ_0_31_DISABLE(I2C1_EVENT_IRQ);
	    NVIC_IRQ_32_63_DISABLE(I2C1_ERROR_IRQ);
	}
	else{
		return;
	}

	// Deinitialize GPIO pins used for I2C
    MCAL_I2C_Reset_GPIO_Pins(I2Cx);
}

void MCAL_I2C_Set_GPIO_Pins(I2C_t *I2Cx){
	GPIO_PinConfig_t PinConfig;
	PinConfig.PinCNF = GPIO_CNF_AF_OPEN_DRAIN_OUTPUT;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	if(I2Cx == I2C1){
		// PB6 and PB7 are used for I2C1
		PinConfig.PinNum = GPIO_PIN6;
		MCAL_GPIO_Init(GPIOB, &PinConfig);
		PinConfig.PinNum = GPIO_PIN7;
		MCAL_GPIO_Init(GPIOB, &PinConfig);
	}
	else if(I2Cx == I2C2){
		// PB10 and PB11 are used for I2C2
		PinConfig.PinNum = GPIO_PIN10;
		MCAL_GPIO_Init(GPIOB, &PinConfig);
		PinConfig.PinNum = GPIO_PIN11;
		MCAL_GPIO_Init(GPIOB, &PinConfig);
	}
	else{
		return;
	}
}

void MCAL_I2C_Master_Transmit_Start(I2C_t *I2Cx) {
    // Ensure the I2C peripheral is enabled
    if (!READ_BIT(I2Cx->CR1, 0)) {
        SET_BIT(I2Cx->CR1, 0); // Enable I2C peripheral
    }

    // Wait until the bus is idle (not busy)
    while (I2C_IsBusBusy(I2Cx) == I2C_BUS_IS_BUSY); // Wait until BUSY flag is cleared

    // Generate START condition
    SET_BIT(I2Cx->CR1, 8); // Set START bit (Bit 8 in CR1)

    // Wait until the START condition is transmitted
    while (I2C_IsStartTransmitted(I2Cx) != I2C_START_IS_TRANSMITTED); // Wait until SB flag is set
}

void MCAL_I2C_Master_Transmit_RepeatedStart(I2C_t *I2Cx){
	// Generate START condition
	SET_BIT(I2Cx->CR1, 8); // Set START bit (Bit 8 in CR1)

	// Wait until the START condition is transmitted
	while (I2C_IsStartTransmitted(I2Cx) != I2C_START_IS_TRANSMITTED); // Wait until SB flag is set
}

void MCAL_I2C_Master_Transmit_Stop(I2C_t *I2Cx){
	/*
	 * Bit 9 STOP: Stop generation
		The bit is set and cleared by software, cleared by hardware when a Stop condition is
		detected, set by hardware when a timeout error is detected.
		In Master Mode:
		0: No Stop generation.
		1: Stop generation after the current byte transfer or after the current Start condition is sent.
		In Slave mode:
		0: No Stop generation.
		1: Release the SCL and SDA lines after the current byte transfer.
	 */
	 SET_BIT(I2Cx->CR1, 9); // Bit 9 STOP: Stop generation
}

void MCAL_I2C_Master_Transmit_Address(I2C_t *I2Cx, uint8 SlaveAddress, I2C_DataDirection_t dataDirection){
	uint8 addressByte = (SlaveAddress << 1) | (dataDirection & 0x01);

	// Send the address byte
	I2Cx->DR = addressByte; // Write address byte to the Data Register (DR)

	// Wait until the address is transmitted and acknowledged
	while(I2C_IsSlaveAddressTransmitted(I2Cx) != I2C_SLAVE_ADDRESS_IS_TRANSMITTED);

	(void)I2Cx->SR1; // Read SR1 first
	(void)I2Cx->SR2; // Then read SR2
}

void MCAL_Transmit_Byte(I2C_t *I2Cx, uint8 byte){
	// Wait till TXE = 1 (Transmit buffer is empty)
	while(I2C_IsTransmitBufferEmpty(I2Cx) != I2C_TRANSMIT_BUFFER_EMPTY);
	// Send the data byte
	I2Cx->DR = byte;
}

uint8 MCAL_Recieve_With_ACK(I2C_t *I2Cx){
	// Enable ACK (Acknowledge) for the received byte
	SET_BIT(I2Cx->CR1, 10); // Bit 10 ACK: Acknowledge enable

	// Wait until the receive buffer is not empty (RXNE = 1)
	 while (I2C_IsRecieveBufferEmpty(I2Cx) == I2C_RECIEVE_BUFFER_EMPTY);

	 // Read the received byte from the Data Register
	 uint8 RecievedByte = I2Cx->DR ;
	 return RecievedByte;
}

uint8 MCAL_Recieve_With_NACK(I2C_t *I2Cx){
	 // Enable NACK (Not Acknowledge) for the received byte
	 CLEAR_BIT(I2Cx->CR1, 10); // Bit 10 ACK: Acknowledge disable

	 // Wait until the receive buffer is not empty (RXNE = 1)
	 while (I2C_IsRecieveBufferEmpty(I2Cx) == I2C_RECIEVE_BUFFER_EMPTY);

	 // Read the received byte from the Data Register
	 uint8 RecievedByte = I2Cx->DR ;
	 return RecievedByte;
}

void MCAL_I2C_Master_Transmit(I2C_t *I2Cx, uint8 SlaveAddress, uint8 *dataOut, uint8 length){
	// Send START condition
	MCAL_I2C_Master_Transmit_Start(I2Cx);

	// Send slave address with write direction (0)
	MCAL_I2C_Master_Transmit_Address(I2Cx, SlaveAddress, I2C_DIRECTION_WRITE);

	// Send data byte by byte
	for(uint8 i = 0; i < length; i++){
		MCAL_Transmit_Byte(I2Cx, dataOut[i]);
	}

	// Wait till last byte is transferred
	while (!READ_BIT(I2Cx->SR1, 2)); // Wait until BTF flag is set

	// Send Stop Condition
	MCAL_I2C_Master_Transmit_Stop(I2Cx);
}

void MCAL_I2C_Master_Reieve(I2C_t *I2Cx, uint8 SlaveAddress, uint8 *dataIn, uint8 length){
	// Send START condition
	MCAL_I2C_Master_Transmit_Start(I2Cx);

	// Send slave address with write direction (0)
	MCAL_I2C_Master_Transmit_Address(I2Cx, SlaveAddress, I2C_DIRECTION_READ);

	// Recieve data byte by byte
	for(uint8 i = 0; i < length; i++){
		if(i == (length - 1)){
			dataIn[i] = MCAL_Recieve_With_NACK(I2Cx);
		}
		else{
			dataIn[i] = MCAL_Recieve_With_ACK(I2Cx);
		}
	}

	// Send Stop Condition
	MCAL_I2C_Master_Transmit_Stop(I2Cx);
}

void I2C_Slave_PollingTransmit(I2C_t *I2Cx, uint8 *dataOut, uint8 length){
	// Send data byte by byte
	for(uint8 i = 0; i < length; i++){
		MCAL_Transmit_Byte(I2Cx, dataOut[i]);
	}
	// Wait till last byte is transferred
	while (!READ_BIT(I2Cx->SR1, 2)); // Wait until BTF (Byte Transfer Finished) flag is set
}

void I2C_Slave_PollingReceive(I2C_t *I2Cx, uint8 *dataIn, uint8 length){
	// Recieve data byte by byte
	for(uint8 i = 0; i < length; i++){
		dataIn[i] = MCAL_Recieve_With_NACK(I2Cx);
	}
}



/* ================================================================ */
/* ============================= ISR ============================== */
/* ================================================================ */

void I2C1_EV_IRQHandler(void) {
    uint8 data;

    // Address matched
    if (I2C1->SR1 & (1 << 1)) { // ADDR flag
    	 // Clear ADDR by reading SR1 and SR2
        volatile uint32 temp = I2C1->SR1;
        temp = I2C1->SR2;
    }

    // Byte received
    if (I2C1->SR1 & (1 << 6)) { // RXNE flag
        data = I2C1->DR; // Read received data
        // Call user-defined callback
        I2C_Slave_Receive_Callback(data);
    }

    // Byte transmitted
    if (I2C1->SR1 & (1 << 7)) { // TXE flag
        I2C1->DR = I2C_Slave_Transmit_Callback(); // Send data
    }

    // Stop condition detected
    if (I2C1->SR1 & (1 << 4)) { // STOPF flag
        I2C1->CR1 |= 0x1; // Clear STOPF by setting PE
        // Call user-defined callback
        I2C_Slave_Stop_Callback();
    }
}

void I2C1_ER_IRQHandler(void) {
    if (I2C1->SR1 & (1 << 10)) { // BERR: Bus error
        I2C1->SR1 &= ~(1 << 10); // Clear the flag
        I2C_Error_Bus();
    }

    if (I2C1->SR1 & (1 << 11)) { // ARLO: Arbitration lost
        I2C1->SR1 &= ~(1 << 11); // Clear the flag
        I2C_Error_ArbitrationLost();
    }

    if (I2C1->SR1 & (1 << 8)) { // AF: Acknowledge failure
        I2C1->SR1 &= ~(1 << 8); // Clear the flag
        I2C_Error_AcknowledgeFailure();
    }

    if (I2C1->SR1 & (1 << 9)) { // OVR: Overrun/Underrun
        I2C1->SR1 &= ~(1 << 9); // Clear the flag
        I2C_Error_OverrunUnderrun();
    }

    if (I2C1->SR1 & (1 << 12)) { // PECERR: PEC error in reception
        I2C1->SR1 &= ~(1 << 12); // Clear the flag
        I2C_Error_PEC();
    }
}


