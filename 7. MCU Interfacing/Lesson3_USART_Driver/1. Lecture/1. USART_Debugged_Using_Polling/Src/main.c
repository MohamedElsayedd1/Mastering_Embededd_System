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

#include "stm32f103x6.h"
#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6_USART_driver.h"

void clock_Init();



int main(void)
{
	USART_Config_t UART1_Config = {
	    .USARTx = USART1,                            // Use USART1 instance
	    .wordLength = USART_8_BIT_WORD_LENGTH,       // 8-bit word length
	    .parityMode = USART_DISABLED_PARITY,         // No parity
	    .paritySelect = USART_EVEN_PARITY,           // (Ignored when parity is disabled)
	    .stopBits = USART_1_STOP_BITS,               // 1 stop bit
	    .TxMode = USART_TX_ENABLED,                  // Enable transmission
	    .RxMode = USART_RX_ENABLED,                  // Enable reception
	    .Tx_Interrupt_Enable = USART_TX_INTERRUPT_DISABLED, // Disable TX interrupt
	    .Rx_Interrupt_Enable = USART_RX_INTERRUPT_DISABLED, // Disable RX interrupt
	    .CTS_CTRL = USART_CTS_DISABLED,              // Disable CTS
	    .RTS_CTRL = USART_RTS_DISABLED,              // Disable RTS
	    .baud_rate = 9600,                           // Set baud rate to 9600
	    .USARTx_CallBackFunction = NULL              // No callback function
	};


	// Initializing the clock
	clock_Init();
	// USART Init
	MCAL_USART_Init(&UART1_Config);


	while(1)
	{
		uint16 DataRecieved;
		DataRecieved = MCAL_USART_RecieveByte(&UART1_Config);
		MCAL_USART_TransmitByte(&UART1_Config, DataRecieved);
	}
}

void clock_Init(){
	GPIOA_CLK_EN(); // IO port A clock enabled
	GPIOB_CLK_EN(); // IO port B clock enabled
	AFIO_CLK_EN();  // AFIO cock enabled
}




