/*
 * _7SEGMENT.h
 *
 *  Created on: Nov 29, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef _7SEGMENT__7SEGMENT_H_
#define _7SEGMENT__7SEGMENT_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "STM32F103x6.h"
#include "stm32f103x6_GPIO_driver.h"

/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define ZERO 	0x01
#define ONE 	0x79
#define TWO 	0x24
#define THREE 	0x30
#define FOUR 	0x4C
#define FIVE 	0x12
#define SIX 	0x02
#define SEVEN 	0x19
#define EIGHT 	0x00
#define NINE 	0x10

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

/* ================================================================ */
/* ============= APIs Supported by "HAL KEYPAD DRIVER"============== */
/* ================================================================ */

void _7_segment_init(void);


#endif /* 7SEGMENT__7SEGMENT_H_ */
