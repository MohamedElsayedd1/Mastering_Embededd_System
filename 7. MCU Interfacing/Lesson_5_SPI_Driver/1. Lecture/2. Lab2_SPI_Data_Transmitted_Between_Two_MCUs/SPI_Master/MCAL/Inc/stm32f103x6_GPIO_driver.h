/*
 * stm32f103x6_GPIO_driver.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_GPIO_DRIVER_H_
#define INC_STM32F103X6_GPIO_DRIVER_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1 = 1,
	GPIO_PIN2 = 2,
	GPIO_PIN3 = 3,
	GPIO_PIN4 = 4,
	GPIO_PIN5 = 5,
	GPIO_PIN6 = 6,
	GPIO_PIN7 = 7,
	GPIO_PIN8 = 8,
	GPIO_PIN9 = 9,
	GPIO_PIN10 = 10,
	GPIO_PIN11 = 11,
	GPIO_PIN12 = 12,
	GPIO_PIN13 = 13,
	GPIO_PIN14 = 14,
	GPIO_PIN15 = 15,
}GPIO_PinNum_t;

typedef enum{
	GPIO_INPUT = 0X00,
	GPIO_OUTPUT_10MHZ,
	GPIO_OUTPUT_2MHZ,
	GPIO_OUTPUT_50MHZ,
}GPIO_PinMode_t;

typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}GPIO_PinState_t;

typedef enum {
    GPIO_CNF_ANALOG_INPUT = 0x00,
    GPIO_CNF_FLOATING_INPUT = 0x01,
    GPIO_CNF_PULL_UP_DOWN_INPUT = 0x02,
    GPIO_CNF_RESERVED = 0x03,
    GPIO_CNF_PUSH_PULL_OUTPUT = 0x00,
    GPIO_CNF_OPEN_DRAIN_OUTPUT = 0x01,
    GPIO_CNF_AF_PUSH_PULL_OUTPUT = 0x02,
    GPIO_CNF_AF_OPEN_DRAIN_OUTPUT = 0x03,
} GPIO_PinCNF_t;

typedef struct{
	GPIO_PinNum_t PinNum;
	GPIO_PinMode_t PinMode;
	GPIO_PinState_t PinState;
	GPIO_PinCNF_t PinCNF;
}GPIO_PinConfig_t;

typedef enum{
	GPIO_LOCK_PIN_ERROR,
	GPIO_LOCK_PIN_ENABLED
}GPIO_PinLock_t;


/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define GPIO_LCKK_PIN						16

/* ================================================================ */
/* ============= APIs Supported by "MCAL GPIO DRIVER"============== */
/* ================================================================ */

void MCAL_GPIO_Init(GPIO_t *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_t *GPIOx);

uint8 MCAL_GPIO_ReadPin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber);
uint16 MCAL_GPIO_ReadPort(GPIO_t *GPIOx);

void MCAL_GPIO_WritePin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber, GPIO_PinState_t value);
void MCAL_GPIO_WritePort(GPIO_t *GPIOx, uint16 value);

void MCAL_GPIO_TogglePin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber);

GPIO_PinLock_t MCAL_GPIO_LockPin(GPIO_t *GPIOx, GPIO_PinNum_t PinNumber);

#endif /* INC_STM32F103X6_GPIO_DRIVER_H_ */
