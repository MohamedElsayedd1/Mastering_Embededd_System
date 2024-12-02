################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/stm32f103x6_EXTI_driver.c \
../MCAL/stm32f103x6_GPIO_driver.c 

OBJS += \
./MCAL/stm32f103x6_EXTI_driver.o \
./MCAL/stm32f103x6_GPIO_driver.o 

C_DEPS += \
./MCAL/stm32f103x6_EXTI_driver.d \
./MCAL/stm32f103x6_GPIO_driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/stm32f103x6_EXTI_driver.o: ../MCAL/stm32f103x6_EXTI_driver.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/STM-Projects/stm32f103x6_Drivers/HAL" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/7SEGMENT" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/KEYPAD" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/LCD" -I../Inc -I"D:/STM-Projects/stm32f103x6_Drivers/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/stm32f103x6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/stm32f103x6_GPIO_driver.o: ../MCAL/stm32f103x6_GPIO_driver.c
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/STM-Projects/stm32f103x6_Drivers/HAL" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/7SEGMENT" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/KEYPAD" -I"D:/STM-Projects/stm32f103x6_Drivers/HAL/LCD" -I../Inc -I"D:/STM-Projects/stm32f103x6_Drivers/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/stm32f103x6_GPIO_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

