/*
 * stm32f103x6_RCC_driver.h
 *
 *  Created on: Dec 15, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_RCC_DRIVER_H_
#define INC_STM32F103X6_RCC_DRIVER_H_


/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6.h"

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef enum{
	RCC_HSI_CLOCK,
	RCC_HSE_CLOCK,
	RCC_PLL_CLOCK
}RCC_systemCLK_status_t;

/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define HSI_RC_FREQ					8000000UL   // Internal high frequency oscillator
#define HSE_RC_FREQ					16000000UL  // External high frequency oscillator

/* ================================================================ */
/* ============= APIs Supported by "MCAL RCC DRIVER"============= */
/* ================================================================ */

uint32 MCAL_RCC_GetSYSCLK_Freq();  //
uint32 MCAL_RCC_GetHCLK_Freq();    // AHB Bus Clock
uint32 MCAL_RCC_GetPCLK1_Freq();   // ABP1 Bus Clock
uint32 MCAL_RCC_GetPCLK2_Freq();   // ABP2 Bus Clock


#endif /* INC_STM32F103X6_RCC_DRIVER_H_ */
