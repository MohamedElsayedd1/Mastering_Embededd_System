/*
 * stm32f103x6_EXTI_driver.c
 *
 *  Created on: Dec 1, 2024
 *      Author: Mohamed Elsayed
 */

#include "stm32f103x6_EXTI_driver.h"

/* ================================================================ */
/* ===================== Global Variables ========================= */
/* ================================================================ */

static void (*EXTI_CallBacks[16])(void) = {0}; // Array of pointers to functions

/* ================================================================ */
/* ============= APIs Supported by "EXTI GPIO DRIVER"============== */
/* ================================================================ */

/**
 * @Function: EXTI_SYSCFG
 * @brief    Configures the SYSCFG for the EXTI line associated with the specified GPIO port and pin.
 *
 * @Param[in] port:   Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.) for the EXTI line.
 * @Param[in] PinNum: Pin number associated with the EXTI line (0 to 15).
 *
 * @Retval   None
 *
 * @Note     This function sets the appropriate bits in the AFIO_EXTICRx register to
 *           route the selected GPIO pin to the EXTI line. Ensure the AFIO clock is enabled
 *           before calling this function. Typically, this function is called internally by
 *           the EXTI initialization routine.
 */
static void EXTI_SYSCFG(GPIO_t *port, GPIO_PinNum_t PinNum){
	uint8 shift = (PinNum % 4) * 4;
	uint8 EXTI_Line;

	if (port == GPIOA) {
	    EXTI_Line = EXTI_PAx_LINE; // Assign EXTI line for GPIOA
	}
	else if (port == GPIOB) {
	    EXTI_Line = EXTI_PBx_LINE; // Assign EXTI line for GPIOB
	}
	else if (port == GPIOC) {
	    EXTI_Line = EXTI_PCx_LINE; // Assign EXTI line for GPIOC
	}
	else if (port == GPIOD) {
	    EXTI_Line = EXTI_PDx_LINE; // Assign EXTI line for GPIOD
	}
	else {
	    return; // Exit the function or handle error
	}

	// Map the GPIO pin to the EXTI line in the AFIO_EXTICR[4]
	AFIO->EXTICR[PinNum / 4] &= ~(0xF << shift);
	AFIO->EXTICR[PinNum / 4] |= ((EXTI_Line & 0xF) << shift);
}

/**
 * @Function: NVIC_EnableIRQ
 * @brief    Enables the interrupt in the NVIC for the specified EXTI line.
 *
 * @Param[in] PinNum: The GPIO pin number associated with the EXTI line (0 to 15).
 *
 * @Retval   None
 *
 * @Note     This function maps the EXTI line to the corresponding NVIC IRQ and enables it.
 *           Ensure that the EXTI line is properly configured before enabling the interrupt.
 */
static void NVIC_EnableIRQ(uint8 EXTI_IRQ){
	NVIC_IRQ_ENABLE(EXTI_IRQ);
}

/**
 * @Function: NVIC_DisableIRQ
 * @brief    Disables the interrupt in the NVIC for the specified EXTI line.
 *
 * @Param[in] PinNum: The GPIO pin number associated with the EXTI line (0 to 15).
 *
 * @Retval   None
 *
 * @Note     Use this function to disable the interrupt for a specific EXTI line
 *           when no longer needed or to avoid interrupt handling temporarily.
 */
static void NVIC_DisableIRQ(uint8 EXTI_IRQ){
	NVIC_IRQ_DISABLE(EXTI_IRQ);
}

/**
 * @Function: EXTI_Init
 * @brief    Initializes the EXTI line for the specified pin and configuration.
 *
 * @Param[in] PinConfig: Pointer to the EXTI_PinConfig_t structure that contains
 *                       the configuration information for the specified EXTI line.
 *
 * @Retval   None
 *
 * @Note     Ensure that the pin configuration is valid and that the corresponding
 *           GPIO pin and clock are properly initialized before calling this function.
 */
void EXTI_Init(EXTI_PinConfig_t *PinConfig){
	// Enable clock for SYSCFG
	AFIO_CLK_EN();  // AFIO cock enabled

	// Configure GPIO as input with Input floating
	MCAL_GPIO_Init(PinConfig->port, &(PinConfig->pin));

	// Configure EXTI line, Enable Interrupt Mask, Disable Event Mask
	SET_BIT(EXTI->IMR, PinConfig->pin.PinNum);
	CLEAR_BIT(EXTI->EMR, PinConfig->pin.PinNum);

	// Configure Interrupt Trigger Edge (Falling, Rising, ...)
	switch(PinConfig->trigger){
		case EXTI_FALLING_EDGE :
			SET_BIT(EXTI->FTSR, PinConfig->pin.PinNum);
			CLEAR_BIT(EXTI->RTSR, PinConfig->pin.PinNum);
			break;

		case EXTI_RISING_EDGE :
			CLEAR_BIT(EXTI->FTSR, PinConfig->pin.PinNum);
			SET_BIT(EXTI->RTSR, PinConfig->pin.PinNum);
			break;

		case EXTI_BOTH_EDGES :
			SET_BIT(EXTI->FTSR, PinConfig->pin.PinNum);
			SET_BIT(EXTI->RTSR, PinConfig->pin.PinNum);
			break;
	}

	// Configure SYSCFG
	EXTI_SYSCFG(PinConfig->port, PinConfig->pin.PinNum);

	// Enable NVIC for the corresponding EXTI line
	if((PinConfig->pin.PinNum >= 0) & (PinConfig->pin.PinNum <= 4)){
		NVIC_EnableIRQ(EXTI0_IRQ + PinConfig->pin.PinNum);
	}
	else if((PinConfig->pin.PinNum >= 5) & (PinConfig->pin.PinNum <= 9)){
		NVIC_EnableIRQ(EXTI9_5_IRQ);
	}
	else if((PinConfig->pin.PinNum >= 10) & (PinConfig->pin.PinNum <= 15)){
		NVIC_EnableIRQ(EXTI15_10_IRQ);
	}
	else{
		return;
	}

	// Store the callback
	EXTI_SetCallback(PinConfig->pin.PinNum, PinConfig->CallBackFun);
}

/**
 * @Function: EXTI_Deinit
 * @brief    Deinitializes the specified EXTI line, disabling interrupts and resetting configuration.
 *
 * @Param[in] PinConfig: Pointer to the EXTI_PinConfig_t structure that contains
 *                       the configuration information for the specified EXTI line.
 *
 * @Retval   None
 *
 * @Note     Use this function to clean up or reset an EXTI line before reconfiguring or freeing resources.
 */
void EXTI_Deinit(GPIO_PinNum_t PinNum){
	CLEAR_BIT(EXTI->IMR, PinNum);
	CLEAR_BIT(EXTI->EMR, PinNum);
	CLEAR_BIT(EXTI->RTSR, PinNum);
	CLEAR_BIT(EXTI->FTSR, PinNum);

	// Disable NVIC for the corresponding EXTI line
	if((PinNum >=0) & (PinNum <= 4)){
		NVIC_DisableIRQ(EXTI0_IRQ + PinNum);
	}
	else if((PinNum >= 5) & (PinNum <= 9)){
		NVIC_DisableIRQ(EXTI9_5_IRQ);
	}
	else if((PinNum >= 10) & (PinNum <= 15)){
		NVIC_DisableIRQ(EXTI15_10_IRQ);
	}
	else{
		return;
	}

	// Clear The Call Back Function
	EXTI_CallBacks[PinNum] = NULL;
}

/**
 * @Function: EXTI_SetCallback
 * @brief    Registers a callback function to be executed when the specified EXTI pin triggers an interrupt.
 *
 * @Param[in] PinNum:       The GPIO pin number associated with the EXTI line.
 * @Param[in] CallBackFun:  Pointer to the callback function to be executed on interrupt.
 *
 * @Retval   None
 *
 * @Note     Ensure the callback function is non-blocking and efficient. This function
 *           should be called after initializing the EXTI line.
 */
void EXTI_SetCallback(GPIO_PinNum_t PinNum, void (*CallBackFun)(void)){
	EXTI_CallBacks[PinNum] = CallBackFun;
}


/* ================================================================ */
/* ========================= ISR Functions ======================== */
/* ================================================================ */

void EXTI0_IRQHandler(void){
	// This bit is cleared by writing a ‘1’ into the bit
	SET_BIT(EXTI->PR, 0);
	// Call IRQ Call Back Function
	if (EXTI_CallBacks[0] != NULL) {
		EXTI_CallBacks[0]();
	}
}

void EXTI1_IRQHandler(void){
	// This bit is cleared by writing a ‘1’ into the bit
	SET_BIT(EXTI->PR, 1);
	// Call IRQ Call Back Function
	if (EXTI_CallBacks[1] != NULL) {
		EXTI_CallBacks[1]();
	}
}

void EXTI2_IRQHandler(void){
	// This bit is cleared by writing a ‘1’ into the bit
	SET_BIT(EXTI->PR, 2);
	// Call IRQ Call Back Function
	if (EXTI_CallBacks[2] != NULL) {
		EXTI_CallBacks[2]();
	}
}

void EXTI3_IRQHandler(void){
	// This bit is cleared by writing a ‘1’ into the bit
	SET_BIT(EXTI->PR, 3);
	// Call IRQ Call Back Function
	if (EXTI_CallBacks[3] != NULL) {
		EXTI_CallBacks[3]();
	}
}

void EXTI4_IRQHandler(void){
	// This bit is cleared by writing a ‘1’ into the bit
	SET_BIT(EXTI->PR, 4);
	// Call IRQ Call Back Function
	if (EXTI_CallBacks[4] != NULL) {
		EXTI_CallBacks[4]();
	}
}

void EXTI9_5_IRQHandler(void){
	if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 5)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 5);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[5] != NULL) {
			EXTI_CallBacks[5]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 6)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 6);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[6] != NULL) {
			EXTI_CallBacks[6]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 7)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 7);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[7] != NULL) {
			EXTI_CallBacks[7]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 8)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 8);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[8] != NULL) {
			EXTI_CallBacks[8]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 9)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 9);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[9] != NULL) {
			EXTI_CallBacks[9]();
		}
	}
}

void EXTI15_10_IRQHandler(void){
	if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 10)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 10);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[10] != NULL) {
			EXTI_CallBacks[10]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 11)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 11);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[11] != NULL) {
			EXTI_CallBacks[11]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 12)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 12);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[12] != NULL) {
			EXTI_CallBacks[12]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 13)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 13);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[13] != NULL) {
			EXTI_CallBacks[13]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 14)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 14);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[14] != NULL) {
			EXTI_CallBacks[14]();
		}
	}
	else if(EXTI_INTERRUPET_TRIGGERED == READ_BIT(EXTI->PR, 15)){
		// This bit is cleared by writing a ‘1’ into the bit
		SET_BIT(EXTI->PR, 15);
		// Call IRQ Call Back Function
		if (EXTI_CallBacks[15] != NULL) {
			EXTI_CallBacks[15]();
		}
	}
}
