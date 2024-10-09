/*
	@Author : Mohamed Elsayed
	@file : main.c
	@Date : 16/09/2024
*/

#include <stdint.h>

#define SYSCTL_RCGCGPIO_R 		(*((volatile uint32_t *)0x400FE108))
#define GPIO_PORTF_DIR_R		(*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_DEN_R		(*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTF_DATA_R		(*((volatile uint32_t *)0x400253FC))

void delayMs(volatile int count);
void GPIO_Init(void);

const int constantVar = 10; // stored in .rodata(Flash)
int arr[3] = {11, 22, 33}; // global vairables stored in .data(Flash -> Sram)
int arr_2[3]; // unintialized global variable -> .bss(Sram)

int main(void)
{

	GPIO_Init();
	 
	while(1){
		// Toggle PF3
		GPIO_PORTF_DATA_R ^= (1 << 3);
		delayMs(500); // Delay for 500ms
	}

	return 0;
}

void delayMs(volatile int count) {
	for (volatile uint32_t i = 0; i < count; i++)
		for (volatile uint32_t j = 0; j < 3180; j++){}  // Approximate delay for 1 ms
}

void GPIO_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;	// Enable clock for Port F 0010 0000 A B C D E F (bit 5 is set)
	// delay to make sure that GPIOF clock is enabled
	delayMs(100);
	GPIO_PORTF_DIR_R |= (1 << 3);	// Set PF3 as output (0b1000 = 0x08)
	GPIO_PORTF_DEN_R |= (1 << 3);	// Enable digital function for PF3
}