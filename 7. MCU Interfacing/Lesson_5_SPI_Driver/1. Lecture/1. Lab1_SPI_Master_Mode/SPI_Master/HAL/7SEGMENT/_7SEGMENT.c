/*
 * _7SEGMENT.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Mohamed Elsayed
 */



#include "_7SEGMENT.h"

/* ========================================== */
/* ========== Functions Definitions ========= */
/* ========================================== */

GPIO_PinConfig_t PinConfig;

void _7_segment_init(void)
{
	// We are connecting 7 segment to Port B from PB9 to PB15
	// We will Initialize the 7 PINS as Output

	// PB9 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN9;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB10 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN10;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB11 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN11;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB12 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN12;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB13 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN13;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB14 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN14;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);

	// PB15 is Output push-pull : Speed 10 MHz
	PinConfig.PinNum = GPIO_PIN15;
	PinConfig.PinMode = GPIO_OUTPUT_10MHZ;
	PinConfig.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT;
	MCAL_GPIO_Init(GPIOB, &PinConfig);
}
