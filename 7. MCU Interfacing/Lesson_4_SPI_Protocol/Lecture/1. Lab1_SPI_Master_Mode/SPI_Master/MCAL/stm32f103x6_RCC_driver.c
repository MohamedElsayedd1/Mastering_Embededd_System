/*
 * stm32f103x6_RCC_driver.c
 *
 *  Created on: Dec 15, 2024
 *      Author: Mohamed Elsayed
 */

#include "stm32f103x6_RCC_driver.h"

static const uint32 AHP_Prescaler_Table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
static const uint32 ABP_Prescaler_Table[8] = {0, 0, 0, 0, 1, 2, 3, 4};

uint32 MCAL_RCC_GetSYSCLK_Freq(){
	switch((RCC->CFGR >> 2) & 0x3){
		case RCC_HSI_CLOCK :
			return HSI_RC_FREQ;
			break;
		case RCC_HSE_CLOCK :
			return HSE_RC_FREQ;
			break;
		case RCC_PLL_CLOCK :
			// Select PLLSRC, Choose PLLMUL, Return PLLCLK
			break;
	}
	return RCC_HSI_CLOCK; // by default
}

uint32 MCAL_RCC_GetHCLK_Freq(){
	uint32 SYSCLK = MCAL_RCC_GetSYSCLK_Freq();
	// Find AHB Prescale from and shift the index from @AHP_Prescaler_Table
	/*
	  Bits 7:4 HPRE[3:0]: AHB prescaler
			Set and cleared by software to control AHB clock division factor.
			0xxx: SYSCLK not divided
			1000: SYSCLK divided by 2
			1001: SYSCLK divided by 4
			1010: SYSCLK divided by 8
			1011: SYSCLK divided by 16
			1100: SYSCLK divided by 64
			1101: SYSCLK divided by 128
			1110: SYSCLK divided by 256
			1111: SYSCLK divided by 512
	 */
	uint32 AHB_Prescale = ((RCC->CFGR >> 4) & 0xF);
	uint32 HCLK = ((uint32)SYSCLK >> AHP_Prescaler_Table[AHB_Prescale]);
	return HCLK;
}

uint32 MCAL_RCC_GetPCLK1_Freq(){
	uint32 HCLK = MCAL_RCC_GetHCLK_Freq();
	/*
	  Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
		Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	*/
	uint32 ABP1_Prescale = ((RCC->CFGR >> 8) & 0x3);
	uint32 PCLK1 = ((uint32)HCLK >> ABP_Prescaler_Table[ABP1_Prescale]);
	return PCLK1;
}

uint32 MCAL_RCC_GetPCLK2_Freq(){
	uint32 HCLK = MCAL_RCC_GetHCLK_Freq();
	/*
	   Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
		Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	 */
	uint32 ABP2_Prescale = ((RCC->CFGR >> 11) & 0x3);
	uint32 PCLK2 = ((uint32)HCLK >> ABP_Prescaler_Table[ABP2_Prescale]);
	return PCLK2;
}
