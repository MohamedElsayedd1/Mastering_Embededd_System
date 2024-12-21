/*
 * stm32f103x6_GPIO_driver.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Mohamed Elsayed
 */

#include "stm32f103x6_GPIO_driver.h"

/**
 * @Function: MCAL_GPIO_Init
 * @brief    Initializes a specified GPIO pin with the given configuration.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  PinConfig: Pointer to a GPIO_PinConfig_t structure containing pin configuration (pin number, mode, speed).
 *
 * @Retval    None
 *
 * @Note      This function must be called before performing any operation on the pin.
 */
void MCAL_GPIO_Init(GPIO_t *GPIOx, GPIO_PinConfig_t *PinConfig){
	volatile uint32 *configRegister = NULL;
	uint8 shift = 0;
	uint8 pin = PinConfig->PinNum ;

	if(pin >= 0 && pin <= 7){
		// Port configuration register low (GPIOx_CRL) 0>>7
		configRegister = &(GPIOx->CRL);
		shift = (pin * 4);
	}
	else if(pin >= 8 && pin <= 15){
		// Port configuration register high (GPIOx_CRH) 8>>15
		configRegister = &(GPIOx->CRH);
		shift = ((pin - 8) * 4);
	}
	else{
		return;
	}

	// Clear the current configuration for the pin
	*configRegister &= ~(0xF << shift);

	if(PinConfig->PinCNF == GPIO_CNF_PULL_UP_DOWN_INPUT){
		// Configure Pin State : High OR Low
		if(PinConfig->PinState == GPIO_HIGH){
			SET_BIT(GPIOx->ODR, PinConfig->PinNum);		 // Enable pull-up
		}
		else{
			CLEAR_BIT(GPIOx->ODR, PinConfig->PinNum);	// Enable pull-down
		}
	}

	// Set the mode and configuration
	*configRegister |= ((PinConfig->PinMode & 0x03) << shift);		 // MODE[1:0]
	*configRegister |= ((PinConfig->PinCNF & 0x03) << (shift+2));	 // CNF[1:0]


}

/**
 * @Function: MCAL_GPIO_DeInit
 * @brief    Resets all the pins of a specified GPIO port to their default states.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 *
 * @Retval    None
 *
 * @Note      This function resets all pins of the specified port. Use caution if other pins are in use.
 */
void MCAL_GPIO_DeInit(GPIO_t *GPIOx){
	if(GPIOx == GPIOA){
		// Set and Reset IOPARST in RCC_APB2RSTR
		SET_BIT(RCC->APB2RSTR, 2);
		CLEAR_BIT(RCC->APB2RSTR, 2);
	}
	else if(GPIOx == GPIOB){
		// Set and Reset IOPBRST in RCC_APB2RSTR
		SET_BIT(RCC->APB2RSTR, 3);
		CLEAR_BIT(RCC->APB2RSTR, 3);
	}
	else if(GPIOx == GPIOC){
		// Set and Reset IOPCRST in RCC_APB2RSTR
		SET_BIT(RCC->APB2RSTR, 4);
		CLEAR_BIT(RCC->APB2RSTR, 4);
	}
	else if(GPIOx == GPIOD){
		// Set and Reset IOPDRST in RCC_APB2RSTR
		SET_BIT(RCC->APB2RSTR, 5);
		CLEAR_BIT(RCC->APB2RSTR, 5);
	}
	else{
		return;
	}
}

/**
 * @Function: MCAL_GPIO_ReadPin
 * @brief    Reads the state of a specified GPIO pin.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  PinNumber: Pin number to be read (0-15).
 *
 * @Retval    uint8: The state of the pin (0: Low, 1: High).
 *
 * @Note      Ensure the pin is configured as an input before calling this function.
 */
uint8 MCAL_GPIO_ReadPin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber){
	// Ensure valid pin number
	if (PinNumber > 15) {
		return 0xFF;  // Return error code for invalid pin number
	}
	return READ_BIT(GPIOx->IDR, PinNumber);
}

/**
 * @Function: MCAL_GPIO_ReadPort
 * @brief    Reads the state of all pins in a specified GPIO port.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 *
 * @Retval    uint16: The state of all pins in the port.
 *
 * @Note      This function reads the entire port register and returns the 16-bit value.
 */
uint16 MCAL_GPIO_ReadPort(GPIO_t *GPIOx){
	return GPIOx->IDR;
}

/**
 * @Function: MCAL_GPIO_WritePin
 * @brief    Writes a value (0 or 1) to a specified GPIO pin.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  PinNumber: Pin number to be written (0-15).
 * @Param[in]  value: The value to be written (0: Reset, 1: Set).
 *
 * @Retval    None
 *
 * @Note      Ensure the pin is configured as an output before calling this function.
 */
void MCAL_GPIO_WritePin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber, GPIO_PinState_t value){
	if(value == GPIO_HIGH){
		SET_BIT(GPIOx->ODR, PinNumber);
	}
	else if(value == GPIO_LOW){
		CLEAR_BIT(GPIOx->ODR, PinNumber);
	}
	else{
		return;
	}
}

/**
 * @Function: MCAL_GPIO_WritePort
 * @brief    Writes a 16-bit value to the output data register (ODR) of the specified GPIO port.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  value: 16-bit value to write to the port. Each bit corresponds to a pin state
 *                    (1: HIGH, 0: LOW).
 *
 * @Retval    None.
 *
 * @Note      - All pins of the port will be updated simultaneously.
 *            - Ensure the GPIO port is properly initialized before calling this function.
 *            - This function does not validate the input parameters. Ensure `GPIOx` is valid.
 */
void MCAL_GPIO_WritePort(GPIO_t *GPIOx, uint16 value) {
    if (GPIOx == NULL) {
        return;  // Ensure the GPIO port pointer is valid
    }

    GPIOx->ODR = value;
}

/**
 * @Function: MCAL_GPIO_TogglePin
 * @brief    Toggles the current state of a specified GPIO pin.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  PinNumber: The pin number to toggle (range: GPIO_PIN0 to GPIO_PIN15).
 *
 * @Retval    None.
 *
 * @Note      - The pin state will switch between HIGH and LOW.
 *            - Ensure the pin is configured as an output before toggling.
 *            - This function does not validate the input parameters. Ensure `GPIOx` is valid
 *              and `PinNumber` is within the valid range.
 */
void MCAL_GPIO_TogglePin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber){
	if ((GPIOx == NULL) || (PinNumber > 15)) {
		return;
	}

	GPIOx->ODR ^= (1 << PinNumber);
}

/**
 * @Function: MCAL_GPIO_LockPin
 * @brief    Locks the configuration of a specified GPIO pin to prevent accidental changes.
 *
 * @Param[in]  GPIOx: Pointer to the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @Param[in]  PinNumber: Pin number to be locked (0-15).
 *
 * @Retval    uint8: Lock status (1: Lock successful, 0: Lock failed).
 *
 * @Note      Once a pin is locked, its configuration cannot be changed until a system reset occurs.
 */
GPIO_PinLock_t MCAL_GPIO_LockPin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber){
	GPIO_PinLock_t lck_state = GPIO_LOCK_PIN_ERROR;
	SET_BIT(GPIOx->LCKR, PinNumber);
	/*
	    LOCK key writing sequence:
		Write 1
		Write 0
		Write 1
		Read 0
		Read 1 (this read is optional but confirms that the lock is active)
	 */
	SET_BIT(GPIOx->LCKR, GPIO_LCKK_PIN);
	CLEAR_BIT(GPIOx->LCKR, GPIO_LCKK_PIN);
	SET_BIT(GPIOx->LCKR, GPIO_LCKK_PIN);
	lck_state = READ_BIT(GPIOx->LCKR, GPIO_LCKK_PIN);
	lck_state = READ_BIT(GPIOx->LCKR, GPIO_LCKK_PIN);
	// Optional read sequence to confirm the lock
	if (READ_BIT(GPIOx->LCKR, GPIO_LCKK_PIN)) {
		return GPIO_LOCK_PIN_ENABLED;  // Lock successful
	}

	return GPIO_LOCK_PIN_ERROR;  // Lock failed
}
