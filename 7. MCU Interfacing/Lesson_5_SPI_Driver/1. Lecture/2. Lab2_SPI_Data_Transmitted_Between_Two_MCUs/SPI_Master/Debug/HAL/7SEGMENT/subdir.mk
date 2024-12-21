################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/7SEGMENT/_7SEGMENT.c 

OBJS += \
./HAL/7SEGMENT/_7SEGMENT.o 

C_DEPS += \
./HAL/7SEGMENT/_7SEGMENT.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/7SEGMENT/_7SEGMENT.o: ../HAL/7SEGMENT/_7SEGMENT.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/STM-Projects/stm32f103x6_Drivers/HAL" -I"D:/STM-Projects/stm32f103x6_Drivers/MCAL/Inc" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/7SEGMENT" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/KEYPAD" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/LCD" -I../Inc -I"D:/STM-Projects/stm32f103x6_Drivers/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/7SEGMENT/_7SEGMENT.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

