/*
 * stm32f103x6.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "Util.h"
#include "Platform_Types.h"



/* ================================================================ */
/* ================= Base Addresses of Memories =================== */
/* ================================================================ */

#define SRAM_BASE_ADDRESS					0x20000000
#define FLASH_BASE_ADDRESS					0x08000000
#define SYSTEM_MEMORY_BASE_ADDRESS	     	0x1FFFF000
#define PERIPHERALS_BASE_ADDRESS	     	0x40000000

#define CORTEX_M3_BASE_ADDRESS	     	    0xE0000000
#define NVIC_BASE_ADDRESS                   0xE000E100

// NVIC Interrupt Set-Enable Registers (ISER)
#define NVIC_ISER0                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x000))
#define NVIC_ISER1                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x004))
#define NVIC_ISER2                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x008))

// NVIC Interrupt Clear-Enable Registers (ICER)
#define NVIC_ICER0                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x080))
#define NVIC_ICER1                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x084))
#define NVIC_ICER2                         *((volatile uint32 *)(NVIC_BASE_ADDRESS + 0x088))


/* ================================================================ */
/* ====== AHBx and APBx Bus Peripheral Base Addresses ============= */
/* ================================================================ */

/* =========================================== */
/* ====== AHB Peripheral Base Addresses ====== */
/* =========================================== */

//RCC
#define RCC_BASE_ADDRESS					0x40021000


/* =========================================== */
/* ====== APB1 Peripheral Base Addresses ===== */
/* =========================================== */

/* ==================================== */
/* ======= USART1 Base Addresses ====== */
/* ==================================== */
#define USART1_BASE_ADDRESS					0x40013800

/* ==================================== */
/* ===== SPI2 Base Addresses ========== */
/* ==================================== */
#define SPI2_BASE_ADDRESS					0x40003800

/* =========================================== */
/* ====== APB2 Peripheral Base Addresses ===== */
/* =========================================== */

/* ==================================== */
/* ======== GPIO Base Addresses ======= */
/* ==================================== */
#define GPIOA_BASE_ADDRESS					0x40010800
#define GPIOB_BASE_ADDRESS					0x40010C00
#define GPIOC_BASE_ADDRESS					0x40011000
#define GPIOD_BASE_ADDRESS					0x40011400

/* ==================================== */
/* ======== EXTI Base Addresses ======= */
/* ==================================== */
#define EXTI_BASE_ADDRESS					0x40010400

/* ==================================== */
/* ======== AFIO Base Addresses ======= */
/* ==================================== */
#define AFIO_BASE_ADDRESS					0x40010000

/* ==================================== */
/* ===== USART 2-3 Base Addresses ===== */
/* ==================================== */
#define USART2_BASE_ADDRESS					0x40004400
#define USART3_BASE_ADDRESS					0x40004800

/* ==================================== */
/* ===== SPI1 Base Addresses ========== */
/* ==================================== */
#define SPI1_BASE_ADDRESS					0x40013000

/* ================================================================ */
/* ===== Peripheral Register Type Definitions (Structures)========= */
/* ================================================================ */

/* ==================================== */
/* ===== Peripheral Register : RCC ==== */
/* ==================================== */

typedef struct{
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 APB2ENR;
	volatile uint32 APB1ENR;
	volatile uint32 BDCR;
	volatile uint32 CSR;
}RCC_t;

/* ==================================== */
/* ==== Peripheral Register : GPIO ==== */
/* ==================================== */

typedef struct{
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
}GPIO_t;

/* ==================================== */
/* ==== Peripheral Register : AFIO ==== */
/* ==================================== */

typedef struct{
    volatile uint32 EVCR;
    volatile uint32 MAPR;
    volatile uint32 EXTICR[4];
    volatile uint32 RESERVED;
    volatile uint32 MAPR2;
} AFIO_t;

/* ==================================== */
/* ==== Peripheral Register : EXTI ==== */
/* ==================================== */

typedef struct{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
}EXTI_t;


/* ==================================== */
/* ==== Peripheral Register : USART === */
/* ==================================== */

typedef struct{
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 BRR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 CR3;
	volatile uint32 GTPR;
}USART_t;

/* ==================================== */
/* ==== Peripheral Register : SPI ===== */
/* ==================================== */

typedef struct{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 CPCPR;
	volatile uint32 RXCRCR;
	volatile uint32 TXCRCR;
	volatile uint32 I2SCFGR;
	volatile uint32 I2SPR;
}SPI_t;


/* ================================================================ */
/* =================== Peripheral Instants  ======================= */
/* ================================================================ */

#define RCC							        ((RCC_t *)(RCC_BASE_ADDRESS))

#define GPIOA							    ((GPIO_t *)(GPIOA_BASE_ADDRESS))
#define GPIOB							    ((GPIO_t *)(GPIOB_BASE_ADDRESS))
#define GPIOC							    ((GPIO_t *)(GPIOC_BASE_ADDRESS))
#define GPIOD							    ((GPIO_t *)(GPIOD_BASE_ADDRESS))

#define AFIO							    ((AFIO_t *)(AFIO_BASE_ADDRESS))

#define EXTI								((EXTI_t *)(EXTI_BASE_ADDRESS))

#define USART1								((USART_t *)(USART1_BASE_ADDRESS))
#define USART2								((USART_t *)(USART2_BASE_ADDRESS))
#define USART3								((USART_t *)(USART3_BASE_ADDRESS))

#define SPI1								((SPI_t *)(SPI1_BASE_ADDRESS))
#define SPI2     							((SPI_t *)(SPI2_BASE_ADDRESS))


/* ================================================================ */
/* =========== Clock Enable/Disable/Reset Macros ================== */
/* ================================================================ */

#define GPIOA_CLK_EN()						SET_BIT(RCC->APB2ENR, 2)
#define GPIOA_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 2)

#define GPIOB_CLK_EN()						SET_BIT(RCC->APB2ENR, 3)
#define GPIOB_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 3)

#define GPIOC_CLK_EN()						SET_BIT(RCC->APB2ENR, 4)
#define GPIOC_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 4)

#define GPIOD_CLK_EN()						SET_BIT(RCC->APB2ENR, 5)
#define GPIOD_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 5)

#define AFIO_CLK_EN()						SET_BIT(RCC->APB2ENR, 0)
#define AFIO_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 0)

#define USART1_CLK_EN()						SET_BIT(RCC->APB2ENR, 14)
#define USART1_CLK_DIS()					CLEAR_BIT(RCC->APB2ENR, 14)
#define USART1_CLK_RST()					SET_BIT(RCC->APB2RSTR, 14)

#define USART2_CLK_EN()						SET_BIT(RCC->APB2ENR, 17)
#define USART2_CLK_DIS()					CLEAR_BIT(RCC->APB2ENR, 17)
#define USART2_CLK_RST()					SET_BIT(RCC->APB2RSTR, 17)

#define USART3_CLK_EN()						SET_BIT(RCC->APB2ENR, 18)
#define USART3_CLK_DIS()					CLEAR_BIT(RCC->APB2ENR, 18)
#define USART3_CLK_RST()					SET_BIT(RCC->APB2RSTR, 18)

#define SPI1_CLK_EN()						SET_BIT(RCC->APB2ENR, 12)
#define SPI1_CLK_DIS()						CLEAR_BIT(RCC->APB2ENR, 12)
#define SPI1_CLK_RST()						SET_BIT(RCC->APB2RSTR, 12)

#define SPI2_CLK_EN()						SET_BIT(RCC->APB1ENR, 14)
#define SPI2_CLK_DIS()						CLEAR_BIT(RCC->APB1ENR, 14)
#define SPI2_CLK_RST()						SET_BIT(RCC->APB1RSTR, 14)

/* ================================================================ */
/* ================= Interrupt Vector Table ======================= */
/* ================================================================ */

// GPIO IRQ Numbers
#define EXTI0_IRQ                            6
#define EXTI9_5_IRQ                          23
#define EXTI15_10_IRQ                        40

// USART IRQ Numbers
#define USART1_IRQ                           37
#define USART2_IRQ                           38
#define USART3_IRQ                           39

// SPI IRQ Numbers
#define SPI1_IRQ                             35
#define SPI2_IRQ                             36

/* ==================================== */
/* == NVIC IRQ Enable/Disable Macros == */
/* ==================================== */

#define NVIC_IRQ_0_31_ENABLE(irq)				SET_BIT(NVIC_ISER0, irq)
#define NVIC_IRQ_0_31_DISABLE(irq)				SET_BIT(NVIC_ICER0, irq)

#define NVIC_IRQ_32_63_ENABLE(irq)				SET_BIT(NVIC_ISER1, irq)
#define NVIC_IRQ_32_63_DISABLE(irq)				SET_BIT(NVIC_ICER1, irq)

#define NVIC_IRQ_64_67_ENABLE(irq)				SET_BIT(NVIC_ISER2, irq)
#define NVIC_IRQ_64_67_DISABLE(irq)				SET_BIT(NVIC_ICER2, irq)

#define NVIC_IRQ_ENABLE(irq)                    \
										do{ \
											if(irq < 32) \
												NVIC_IRQ_0_31_ENABLE(irq); \
											else if(irq < 64) \
												NVIC_IRQ_32_63_ENABLE(irq - 32); \
											else \
												NVIC_IRQ_64_67_ENABLE(irq - 64); \
										}while(0)

#define NVIC_IRQ_DISABLE(irq)                    \
										do{ \
											if(irq < 32) \
												NVIC_IRQ_0_31_DISABLE(irq); \
											else if(irq < 64) \
												NVIC_IRQ_32_63_DISABLE(irq - 32); \
											else \
												NVIC_IRQ_64_67_DISABLE(irq - 64); \
										}while(0)



/* ================================================================ */
/* ====================== Generic Macros ========================== */
/* ================================================================ */


#endif /* INC_STM32F103X6_H_ */
