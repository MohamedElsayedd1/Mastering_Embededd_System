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

//#define MCU_SPI_MASTER
#define MCU_SPI_SLAVE

#include "stm32f103x6.h"
#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6_USART_driver.h"
#include "stm32f103x6_SPI_driver.h"
#include "stm32f103x6_I2C_driver.h"
#include "stm32f103x6_SLAVE_EEPROM_Driver.h"

void clock_Init();
void MyUSART1_IRQHandler(void);
void MySPI1_IRQHandler(void);

//USART_Config_t UART1_Config = {
//	.USARTx = USART1,                            // Use USART1 instance
//	.wordLength = USART_8_BIT_WORD_LENGTH,       // 8-bit word length
//	.parityMode = USART_DISABLED_PARITY,         // No parity
//	.paritySelect = USART_EVEN_PARITY,           // (Ignored when parity is disabled)
//	.stopBits = USART_1_STOP_BITS,               // 1 stop bit
//	.TxMode = USART_TX_ENABLED,                  // Enable transmission
//	.RxMode = USART_RX_ENABLED,                  // Enable reception
//	.Tx_Interrupt_Enable = USART_TX_INTERRUPT_DISABLED, // Disable TX interrupt
//	.Rx_Interrupt_Enable = USART_RX_INTERRUPT_ENABLED, // Enable RX interrupt
//	.CTS_CTRL = USART_CTS_DISABLED,              // Disable CTS
//	.RTS_CTRL = USART_RTS_DISABLED,              // Disable RTS
//	.baud_rate = 115200,                           // Set baud rate to 115200
//	.USARTx_CallBackFunction = MyUSART1_IRQHandler              // No callback function
//};
//
//#ifdef MCU_SPI_MASTER
//GPIO_PinConfig_t PA4_Pin = {
//	.PinMode = GPIO_OUTPUT_10MHZ,
//	.PinNum = GPIO_PIN4,
//	.PinCNF = GPIO_CNF_PUSH_PULL_OUTPUT
//};
//#endif
//
//#ifdef MCU_SPI_MASTER
//SPI_Config_t SPI1_Config = {
//	.SPIx = SPI1,
//	.clockPhase = SPI_CPHA_SECOND_EDGE,
//	.clockPolarity = SPI_CPOL_HIGH,
//	.dataSize = SPI_DATASIZE_8BIT,
//	.frameFormat = SPI_DFF_MSB_FIRST,
//	.bidirectionalMode = SPI_BDM_2LINE_UNIDIR,
//	.mode = SPI_MODE_MASTER,
//	.txeInterrupt = SPI_TXE_IRQ_DISABLED,
//	.rxneInterrupt = SPI_RXNE_IRQ_DISABLED,
//	.baudRate = SPI_BAUDRATE_FPCLK_DIV_8,
//	.ssm = SPI_SSM_ENABLED,    // Software NSS management
//	.SPI_CallBackFun = NULL
//};
//#endif
//
//#ifdef MCU_SPI_SLAVE
//SPI_Config_t SPI1_Config = {
//	.SPIx = SPI1,
//	.clockPhase = SPI_CPHA_SECOND_EDGE,
//	.clockPolarity = SPI_CPOL_HIGH,
//	.dataSize = SPI_DATASIZE_8BIT,
//	.frameFormat = SPI_DFF_MSB_FIRST,
//	.bidirectionalMode = SPI_BDM_2LINE_UNIDIR,
//	.mode = SPI_MODE_SLAVE,
//	.txeInterrupt = SPI_TXE_IRQ_DISABLED,
//	.rxneInterrupt = SPI_RXNE_IRQ_ENABLED,  // Enable Reciever buffer not empty interrupt
// 	.ssm = SPI_SSM_DISABLED,    // Software NSS management
//	.SPI_CallBackFun = MySPI1_IRQHandler
//
//};
//#endif

int main(void)
{


	// Initializing the clock
	clock_Init();

	uint8 ch1[7] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	uint8 ch2[7] = {0};

	HAL_EEPROM_Init();

	// Test case 1
	HAL_EEPROM_Write_N_Bytes(0xAF, ch1, 7);
	HAL_EEPROM_Read_N_Bytes(0xAF, ch2, 7);

	// Test case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	HAL_EEPROM_Write_N_Bytes(0xFFF, ch1, 7);
	HAL_EEPROM_Read_N_Bytes(0xFFF, ch2, 7);


	while(1)
	{

	}
}

void clock_Init(){
	GPIOA_CLK_EN(); // IO port A clock enabled
	GPIOB_CLK_EN(); // IO port B clock enabled
	AFIO_CLK_EN();  // AFIO cock enabled
}


