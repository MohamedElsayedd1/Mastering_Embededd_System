/*
 * atmega32_TIMER_driver.h
 *
 * Created: 30/01/2025 8:24:55 AM
 *  Author: Mohamed Elsayed
 */ 


#ifndef ATMEGA32_TIMER_DRIVER_H_
#define ATMEGA32_TIMER_DRIVER_H_

// Includes
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "Util.h"
#include "atmega32_GPIO_driver.h"

// Enums
typedef enum{
	TIMER_NORMAL_MODE,
	TIMER_PWM_PHASE_CORRECT_MODE,
	TIMER_CTC_MODE,
	TIMER_PWM_FAST_MODE
}TIMER_Mode_t;

typedef enum{
	TIMER_NORMAL_PORT_OPERATION,
	TIMER_TOGGLE_PIN_ON_COMPARE_MATCH,
	TIMER_CLEAR_PIN_ON_COMPARE_MATCH,
	TIMER_SET_PIN_ON_COMPARE_MATCH
}TIMER_Compare_Match_Output_Mode_t;

typedef enum{
	TIMER_NORMAL_FPWM,
	FPWM_RESERVED,
	TIMER_CLEAR_ON_MATCH_SET_ON_BOTTOM, // Non-Inverting mode Fast PWM
	TIMER_SET_ON_MATCH_CLEAR_ON_BOTTOM,
}TIMER_FPWM_Match_Output_Mode_t;

typedef enum{
	TIMER_NORMAL_PPWM,
	PPPWM_RESERVED,
	TIMER_CLEAR_ON_UP_MATCH_SET_ON_DOWN_MATCH,
	TIMER_SET_ON_UP_MATCH_CLEAR_ON_DOWN_MATCH,
}TIMER_PPWM_Match_Output_Mode_t;

typedef enum{
	TIMER_NO_CLK_SOURCE,
	TIMER_CLK_NO_PRESCELER,
	TIMER_CLK_8_PRESCELER,
	TIMER_CLK_64_PRESCELER,
	TIMER_CLK_265_PRESCELER,
	TIMER_CLK_1024_PRESCELER,
	TIMER_RISING_EXTERNAL_CLK,
	TIMER_FALLING_EXTERNAL_CLK,
}TIMER_Clk_Source_t;

typedef enum{
	TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE,
	TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE,
}TIMER_Output_Compare_Match_Interrupt_t;


typedef enum{
	TIMER_OVERFLOW_INTERRUPT_DISABLE,
	TIMER_OVERFLOW_INTERRUPT_ENABLE,
}TIMER_Overflow_Interrupt_t;

// Structure
typedef struct{
	uint8_t Compare_Value;
	uint8_t Counter_Value;
	uint8_t Timer_dutyCycle;
	TIMER_Mode_t Timer_mode;
	TIMER_Compare_Match_Output_Mode_t Timer_Compare_Match_Output_Mode;
	TIMER_FPWM_Match_Output_Mode_t Timer_FPWM_Match_Output_Mode;
	TIMER_PPWM_Match_Output_Mode_t Timer_PPWM_Match_Output_Mode;
	TIMER_Clk_Source_t Timer_Clk_Src;
	TIMER_Output_Compare_Match_Interrupt_t  Timer_Output_Compare_Match_Interrupt_Enable;
	TIMER_Overflow_Interrupt_t Timer_Overflow_Interrupt_Enable;
}TIMER_config_t;

// API
void TIMER_Init(TIMER_config_t *timerConfig);
void TIMER_Deinit();

void TIMER_Set_Counter(uint8_t timer_value);
uint8_t TIMER_Get_Counter(void);

void TIMER_Set_Compare(uint8_t compare_value);
uint8_t TIMER_Get_Compare(void);

void TIMER_Set_PWM_DutyCycle(uint8_t dutyCycle_value);
uint8_t TIMER_Get_PWM_DutyCycle(void);

void TIMER_Set_Presceler(uint8_t presceler);
uint8_t TIMER_Get_Presceler(void);

#endif /* ATMEGA32_TIMER_DRIVER_H_ */