/*
 * main.c
 *
 * Created: 05/12/2024 7:51:50 PM
 *  Author: Mohamed Elsayed
 */ 

#include <util/delay.h>
#include <xc.h>

#include "atmega32_GPIO_driver.h"
#include "atmega32_HAL_LCD.h"
#include "atmega32_UART_driver.h"
#include "atmega32_I2C_driver.h"
#include "atmega32_TIMER_driver.h"
 


void display_number(uint8_t number) {
	PORTB = number; 
}

int main(void) {
	// Test case 1 : run timer as normal mode
	/*
	TIMER_config_t timer0_normal_mode = {
		.Counter_Value = 0,
		.Compare_Value = 0,
		.Timer_Clk_Src = TIMER_CLK_1024_PRESCELER,
		.Timer_mode = TIMER_NORMAL_MODE,
		.Timer_Compare_Match_Output_Mode = TIMER_NORMAL_PORT_OPERATION,
		.Timer_Overflow_Interrupt_Enable = TIMER_OVERFLOW_INTERRUPT_ENABLE,
		.Timer_Output_Compare_Match_Interrupt_Enable = TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE
	};
	
	GPIO_InitPin(GPIO_PORT_C, PC0, GPIO_PIN_OUTPUT);
	TIMER_Init(&timer0_normal_mode);
	DDRA = 0xff;
	
	while(1){	
		PORTA = TIMER_Get_Counter();
	}
	*/
	
	// Test case 2 : run timer is ctc mode
	/*
	TIMER_config_t timer0_normal_mode = {
		.Counter_Value = 0,
		.Compare_Value = 55,
		.Timer_Clk_Src = TIMER_CLK_1024_PRESCELER,
		.Timer_mode = TIMER_CTC_MODE,
		.Timer_Compare_Match_Output_Mode = TIMER_TOGGLE_PIN_ON_COMPARE_MATCH,
		.Timer_Overflow_Interrupt_Enable = TIMER_OVERFLOW_INTERRUPT_DISABLE,
		.Timer_Output_Compare_Match_Interrupt_Enable = TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE
	};
	
	TIMER_Init(&timer0_normal_mode);
	DDRA = 0xff;
	
	while(1){
		PORTA = TIMER_Get_Counter();
	}
	*/
	
	// Test case 3 : run timer in fast pwm
	/*
	TIMER_config_t timer0_normal_mode = {
		.Counter_Value = 0,
		.Compare_Value = 0,
		.Timer_dutyCycle = 192, // 75% duty cycle 
		.Timer_Clk_Src = TIMER_CLK_1024_PRESCELER,
		.Timer_mode = TIMER_PWM_FAST_MODE,
		.Timer_FPWM_Match_Output_Mode = TIMER_CLEAR_ON_MATCH_SET_ON_BOTTOM,
		.Timer_Overflow_Interrupt_Enable = TIMER_OVERFLOW_INTERRUPT_DISABLE,
		.Timer_Output_Compare_Match_Interrupt_Enable = TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE
	};
	
	TIMER_Init(&timer0_normal_mode);
	DDRA = 0xff;
	
	while(1){
		PORTA = TIMER_Get_Counter();
	}
	*/
	
	// Test case 4 : run timer in phase correct pwm
	/*
	TIMER_config_t timer0_normal_mode = {
		.Counter_Value = 0,
		.Compare_Value = 0,
		.Timer_dutyCycle = 63, // 25% duty cycle
		.Timer_Clk_Src = TIMER_CLK_1024_PRESCELER,
		.Timer_mode = TIMER_PWM_PHASE_CORRECT_MODE,
		.Timer_PPWM_Match_Output_Mode = TIMER_CLEAR_ON_UP_MATCH_SET_ON_DOWN_MATCH,
		.Timer_Overflow_Interrupt_Enable = TIMER_OVERFLOW_INTERRUPT_DISABLE,
		.Timer_Output_Compare_Match_Interrupt_Enable = TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE
	};
	
	TIMER_Init(&timer0_normal_mode);
	DDRA = 0xff;
	
	while(1){
		PORTA = TIMER_Get_Counter();
	}
	*/
	
	// Test case 4 : run timer in external source counter t0, t1
	TIMER_config_t timer0_normal_mode = {
		.Counter_Value = 0,
		.Compare_Value = 4,
		.Timer_dutyCycle = 0, 
		.Timer_Clk_Src = TIMER_RISING_EXTERNAL_CLK,
		.Timer_mode = TIMER_CTC_MODE,
		.Timer_Compare_Match_Output_Mode = TIMER_TOGGLE_PIN_ON_COMPARE_MATCH,
		.Timer_Overflow_Interrupt_Enable = TIMER_OVERFLOW_INTERRUPT_DISABLE,
		.Timer_Output_Compare_Match_Interrupt_Enable = TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE
	};
	
	TIMER_Init(&timer0_normal_mode);
	GPIO_InitPin(GPIO_PORT_B, PB0, GPIO_PIN_INPUT);
	DDRA = 0xff;
	
	while(1){
		PORTA = TIMER_Get_Counter();
	}	

	return 0;
}


