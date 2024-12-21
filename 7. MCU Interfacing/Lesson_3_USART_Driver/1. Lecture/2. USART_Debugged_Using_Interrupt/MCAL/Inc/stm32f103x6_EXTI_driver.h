/*
 * stm32f103x6_EXTI_driver.h
 *
 *  Created on: Dec 1, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_EXTI_DRIVER_H_
#define INC_STM32F103X6_EXTI_DRIVER_H_


/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6.h"
#include "stm32f103x6_GPIO_driver.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef enum{
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE,
	EXTI_BOTH_EDGES,
}EXTI_TriggerType;

typedef struct{
	GPIO_t *port;
	GPIO_PinConfig_t pin;
	EXTI_TriggerType trigger;
	void (*CallBackFun)(void);
}EXTI_PinConfig_t;


/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define EXTI_PAx_LINE 							0x0
#define EXTI_PBx_LINE 							0x1
#define EXTI_PCx_LINE 							0x2
#define EXTI_PDx_LINE 							0x3

#define EXTI_INTERRUPET_TRIGGERED               1
#define EXTI_INTERRUPET_NOT_TRIGGERED           0

/* ================================================================ */
/* ============= APIs Supported by "EXTI GPIO DRIVER"============== */
/* ================================================================ */

void EXTI_Init(EXTI_PinConfig_t *PinConfig);
void EXTI_Deinit(GPIO_PinNum_t PinNum);
void EXTI_SetCallback(GPIO_PinNum_t PinNum, void (*CallBackFun)(void));

#endif /* INC_STM32F103X6_EXTI_DRIVER_H_ */
