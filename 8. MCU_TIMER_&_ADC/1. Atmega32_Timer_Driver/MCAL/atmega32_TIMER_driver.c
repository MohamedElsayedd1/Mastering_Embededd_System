/*
 * atmega32_TIMER_driver.c
 *
 * Created: 30/01/2025 8:25:09 AM
 *  Author:	Mohamed Elsayed
 */ 

#include "atmega32_TIMER_driver.h"

void TIMER_Init(TIMER_config_t *timerConfig){
	
	// Set the clock source
	TCCR0 &= ~(0b111 << 0);
	TCCR0 |= (timerConfig->Timer_Clk_Src << 0);
	
	// Set the mode
	if(timerConfig->Timer_mode == TIMER_NORMAL_MODE){
		RESET_BIT(TCCR0, 6);
		RESET_BIT(TCCR0, 3);
		// Compare Output Mode, non-PWM Mode
		if(timerConfig->Timer_Compare_Match_Output_Mode != TIMER_NORMAL_PORT_OPERATION){
			// Set PB3 as output
			SET_BIT(DDRB, PB3);
		}
		TCCR0 &= ~(0b11 << 4);
		TCCR0 |= (timerConfig->Timer_Compare_Match_Output_Mode << 4);
		// Set timer value
		TIMER_Set_Counter(timerConfig->Counter_Value);
	}
	else if(timerConfig->Timer_mode == TIMER_PWM_PHASE_CORRECT_MODE){
		SET_BIT(TCCR0, 6);
		RESET_BIT(TCCR0, 3);
		//  Compare Output Mode, Phase Correct PWM Mode
		if(timerConfig->Timer_PPWM_Match_Output_Mode != TIMER_NORMAL_PPWM ||
		timerConfig->Timer_PPWM_Match_Output_Mode != PPPWM_RESERVED){
			// Set PB3 as output
			SET_BIT(DDRB, PB3);
		}
		TCCR0 &= ~(0b11 << 4);
		TCCR0 |= (timerConfig->Timer_PPWM_Match_Output_Mode << 4);
		// Set timer value
		TIMER_Set_Counter(timerConfig->Counter_Value);
		// set duty cycle value
		TIMER_Set_PWM_DutyCycle(timerConfig->Timer_dutyCycle);
	}
	else if(timerConfig->Timer_mode == TIMER_CTC_MODE){
		RESET_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);
		// Compare Output Mode, non-PWM Mode
		if(timerConfig->Timer_Compare_Match_Output_Mode != TIMER_NORMAL_PORT_OPERATION){
			// Set PB3 as output
			SET_BIT(DDRB, PB3);
		}
		TCCR0 &= ~(0b11 << 4);
		TCCR0 |= (timerConfig->Timer_Compare_Match_Output_Mode << 4);
		// Set timer value
		TIMER_Set_Counter(timerConfig->Counter_Value);
		// Set compare value
		TIMER_Set_Compare(timerConfig->Compare_Value);
	}
	else if(timerConfig->Timer_mode == TIMER_PWM_FAST_MODE){
		SET_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);
		// Compare Output Mode, Fast PWM Mode(1)
		if(timerConfig->Timer_Compare_Match_Output_Mode != TIMER_NORMAL_FPWM ||
		timerConfig->Timer_Compare_Match_Output_Mode != FPWM_RESERVED){
			// Set PB3 as output
			SET_BIT(DDRB, PB3);
		}
		TCCR0 &= ~(0b11 << 4);
		TCCR0 |= (timerConfig->Timer_FPWM_Match_Output_Mode << 4);
		// Set timer value
		TIMER_Set_Counter(timerConfig->Counter_Value);
		// set duty cycle value
		TIMER_Set_PWM_DutyCycle(timerConfig->Timer_dutyCycle);
	}
	else{
		return;
	}
	
	if(timerConfig->Timer_Output_Compare_Match_Interrupt_Enable == TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE || 
	timerConfig->Timer_Overflow_Interrupt_Enable == TIMER_OVERFLOW_INTERRUPT_ENABLE){
		TIMSK |= (timerConfig->Timer_Output_Compare_Match_Interrupt_Enable << OCIE0);
		TIMSK |= (timerConfig->Timer_Overflow_Interrupt_Enable << TOIE0);
		// Re-enable global interrupts
		sei();
	}
	else{
		// Do nothing
	}
}
void TIMER_Deinit(){
	// No clock source (Timer/Counter stopped).
	// Clear the clock source
	TCCR0 &= ~(0b111 << 0);
	// Reset the TCCR0
	TCCR0 = 0x00;
}

void TIMER_Set_Counter(uint8_t timer_value){
	TCNT0 = (uint8_t)timer_value;
}

uint8_t TIMER_Get_Counter(void){
	return (uint8_t)TCNT0;
}

void TIMER_Set_Compare(uint8_t compare_value){
	OCR0 = (uint8_t)compare_value;	
}

uint8_t TIMER_Get_Compare(void){
	return (uint8_t)OCR0;
}

void TIMER_Set_PWM_DutyCycle(uint8_t dutyCycle_value){
	OCR0 = (uint8_t)dutyCycle_value;	
}

uint8_t TIMER_Get_PWM_DutyCycle(void){
	return (uint8_t)OCR0;
}

void TIMER_Set_Presceler(uint8_t presceler){
	TCCR0 &= ~(0b111 << 0);
	TCCR0 |= (presceler << 0);
}

uint8_t TIMER_Get_Presceler(void){
	return (uint8_t)(TCCR0 & 0x7);
}

ISR(TIM0_OVF){
	GPIO_TogglePin(GPIO_PORT_C, PC0);
}