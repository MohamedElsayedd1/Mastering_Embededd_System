/*
 * Platform_Types.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Mohamed Elsayed
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#include <stdbool.h> // Boolean type

#define NULL                   ((void *)0x00)

#define CPU_TYPE_8             8U
#define CPU_TYPE_16            16U
#define CPU_TYPE_32            32U
#define MSB_FIRST              0U
#define LSB_FIRST              1U
#define HIGH_BYTE_FIRST        0U
#define LOW_BYTE_FIRST         1U

#define CPU_TYPE               CPU_TYPE_8
#define CPU_ORDER_BIT          LSB_FIRST
#define CPU_ORDER_BYTE         LOW_BYTE_FIRST

/* Boolean values */
#ifndef TRUE
#define TRUE                   (Boolean)1
#endif // !TRUE
#ifndef FALSE
#define FALSE                  (Boolean)0
#endif // !FALSE

/* Fixed-width integer types */
typedef _Bool                  boolean;
typedef char                   sint8;
typedef unsigned char          uint8;
typedef short int              sint16;
typedef unsigned short int     uint16;
typedef int                    sint32;
typedef unsigned int           uint32;
typedef long long int          sint64;
typedef unsigned long long int uint64;

/* Fixed-width volatile integer types */
typedef volatile uint8         vuint8;
typedef volatile sint8         vsint8;
typedef volatile uint16        vuint16;
typedef volatile sint16        vsint16;
typedef volatile uint32        vuint32;
typedef volatile sint32        vsint32;
typedef volatile uint64        vuint64;
typedef volatile sint64        vsint64;

/* Floating-point types */
typedef float       float32;
typedef double      float64;

#endif // !PLATFORM_TYPES_H
