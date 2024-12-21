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

#define MCU_SPI_MASTER
//#define MCU_SPI_SLAVE

#include "stm32f103x6.h"
#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6_USART_driver.h"
#include "stm32f103x6_SPI_driver.h"

void clock_Init();
void MyUSART1_IRQHandler(void);

USART_Config_t UART1_Config = {
	.USARTx = USART1,                            // Use USART1 instance
	.wordLength = USART_8_BIT_WORD_LENGTH,       // 8-bit word length
	.parityMode = USART_DISABLED_PARITY,         // No parity
	.paritySelect = USART_EVEN_PARITY,           // (Ignored when parity is disabled)
	.stopBits = USART_1_STOP_BITS,               // 1 stop bit
	.TxMode = USART_TX_ENABLED,                  // Enable transmission
	.RxMode = USART_RX_ENABLED,                  // Enable reception
	.Tx_Interrupt_Enable = USART_TX_INTERRUPT_DISABLED, // Disable TX interrupt
	.Rx_Interrupt_Enable = USART_RX_INTERRUPT_ENABLED, // Enable RX interrupt
	.CTS_CTRL = USART_CTS_DISABLED,              // Disable CTS
	.RTS_CTRL = USART_RTS_DISABLED,              // Disable RTS
	.baud_rate = 115200,                           // Set baud rate to 115200
	.USARTx_CallBackFunction = MyUSART1_IRQHandler              // No callback function
};

#ifdef MCU_SPI_MASTER
GPIO_PinConfig_t PA4_Pin = {
	.PinMode = GPIO_OUTPUT_10MHZ,
	.PinNum = GPIO_PIN4,
	.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT
};
#endif

#ifdef MCU_SPI_MASTER
SPI_Config_t SPI1_Config = {
	.SPIx = SPI1,
	.clockPhase = SPI_CPHA_SECOND_EDGE,
	.clockPolarity = SPI_CPOL_HIGH,
	.dataSize = SPI_DATASIZE_8BIT,
	.frameFormat = SPI_DFF_MSB_FIRST,
	.bidirectionalMode = SPI_BDM_2LINE_UNIDIR,
	.mode = SPI_MODE_MASTER,
	.txeInterrupt = SPI_TXE_IRQ_DISABLED,
	.rxneInterrupt = SPI_RXNE_IRQ_DISABLED,
	.baudRate = SPI_BAUDRATE_FPCLK_DIV_8,
	.ssm = SPI_SSM_ENABLED,    // Software NSS management
	.SPI_CallBackFun = NULL
};
#endif

#ifdef MCU_SPI_SLAVE
SPI_Config_t SPI1_Config = {
	.SPIx = SPI1,
	.clockPhase = SPI_CPHA_SECOND_EDGE,
	.clockPolarity = SPI_CPOL_HIGH,
	.dataSize = SPI_DATASIZE_8BIT,
	.frameFormat = SPI_DFF_MSB_FIRST,
	.bidirectionalMode = SPI_BDM_2LINE_UNIDIR,


};
#endif

int main(void)
{


	// Initializing the clock
	clock_Init();
	// Initialize PA4
	#ifdef MCU_SPI_MASTER
	MCAL_GPIO_Init(GPIOA, &PA4_Pin);
	// Set the logic of PA4 to HIGH
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_HIGH);
	#endif
	// Initializing USART1
	MCAL_USART_Init(&UART1_Config);
	// Initializing SPI1
	MCAL_SPI_Init(&SPI1_Config);


	while(1)
	{

	}
}

void clock_Init(){
	GPIOA_CLK_EN(); // IO port A clock enabled
	GPIOB_CLK_EN(); // IO port B clock enabled
	AFIO_CLK_EN();  // AFIO cock enabled
}

void MyUSART1_IRQHandler(void)
{
	#ifdef MCU_SPI_MASTER
	uint16 received_byte = USART1->DR;
	USART1->DR = received_byte;
	// Transmit Data on SPI
	// Set the logic of PA4 to LOW
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN4,  GPIO_LOW);  // Chip select
	uint16 RecievedDataFromSPI = MCAL_SPI_Transmit_Recieve(&SPI1_Config, received_byte);
	// Set the logic of PA4 to LOW
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN4,  GPIO_HIGH);  // Chip select
	#endif
}

