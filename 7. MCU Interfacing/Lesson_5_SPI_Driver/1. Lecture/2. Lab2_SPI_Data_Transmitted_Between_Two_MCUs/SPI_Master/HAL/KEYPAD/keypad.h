/*
 * keypad.h
 *
 *  Created on: Nov 29, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef _KEYPAD_H_
#define _KEYPAD_H_


/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6.h"

/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define KEYPAD_ROWS                 4
#define KEYPAD_COLUMNS              4

#define KEYPAD_PORT GPIOB


#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN3
#define R3 GPIO_PIN4
#define C0 GPIO_PIN5
#define C1 GPIO_PIN6
#define C2 GPIO_PIN7
#define C3 GPIO_PIN8


/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */


/* ================================================================ */
/* ============= APIs Supported by "HAL KEYPAD DRIVER"============== */
/* ================================================================ */

void Keypad_init();
char Keypad_getkey();


#endif
