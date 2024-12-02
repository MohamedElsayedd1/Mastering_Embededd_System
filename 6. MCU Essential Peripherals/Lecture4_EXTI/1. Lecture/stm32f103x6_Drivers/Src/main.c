/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Elsayed
 * @brief          : Main program body
 ******************************************************************************
 **/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "lcd.h"
#include "keypad.h"
#include "_7SEGMENT.h"
#include "stm32f103x6_EXTI_driver.h"

void MY_EXTI9_ISR(void);
void clock_Init();

lcd_t lcd1 = {
		.DataRegister = GPIOA,
		.ControlRegister = GPIOA,

		.DataPins[0].PinNum = GPIO_PIN0,
		.DataPins[0].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[0].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[0].PinState = GPIO_LOW,

		.DataPins[1].PinNum = GPIO_PIN1,
		.DataPins[1].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[1].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[1].PinState = GPIO_LOW,

		.DataPins[2].PinNum = GPIO_PIN2,
		.DataPins[2].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[2].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[2].PinState = GPIO_LOW,

		.DataPins[3].PinNum = GPIO_PIN3,
		.DataPins[3].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[3].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[3].PinState = GPIO_LOW,

		.DataPins[4].PinNum = GPIO_PIN4,
		.DataPins[4].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[4].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[4].PinState = GPIO_LOW,

		.DataPins[5].PinNum = GPIO_PIN5,
		.DataPins[5].PinMode = GPIO_OUTPUT_2MHZ,
		.DataPins[5].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[5].PinState = GPIO_LOW,

		.DataPins[6].PinNum = GPIO_PIN6,
		.DataPins[6].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[6].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[6].PinState = GPIO_LOW,

		.DataPins[7].PinNum = GPIO_PIN7,
		.DataPins[7].PinMode = GPIO_OUTPUT_10MHZ,
		.DataPins[7].PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.DataPins[7].PinState = GPIO_LOW,

		.RS.PinNum = GPIO_PIN8,
		.RS.PinMode = GPIO_OUTPUT_10MHZ,
		.RS.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.RS.PinState = GPIO_LOW,

		.EN.PinNum = GPIO_PIN9,
		.EN.PinMode = GPIO_OUTPUT_10MHZ,
		.EN.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT,
		.EN.PinState = GPIO_LOW,
};

EXTI_PinConfig_t EXTI9_Pin = {
		GPIOB,
		{GPIO_PIN9, GPIO_INPUT, GPIO_LOW, GPIO_CNF_FLOATING_INPUT},
		EXTI_RISING_EDGE,
		MY_EXTI9_ISR
};

int main(void)
{
	// Initializing the clock
	clock_Init();
	// Initializing LCD
	lcd_initialize(&lcd1);
	// Initializing EXTI9 Pin
	EXTI_Init(&EXTI9_Pin);

	while(1)
	{

	}
}

void clock_Init(){
	GPIOA_CLK_EN(); // IO port A clock enabled
	GPIOB_CLK_EN(); // IO port B clock enabled
	AFIO_CLK_EN();  // AFIO cock enabled
}

void MY_EXTI9_ISR(void){
	lcd_send_string_pos(&lcd1, "IRQ9 EXTI is", 1, 1);
	lcd_send_string_pos(&lcd1, "happened _|-", 2, 1);
	_delay_ms(1000);
	lcd_send_command(&lcd1, _LCD_CLEAR);
}



