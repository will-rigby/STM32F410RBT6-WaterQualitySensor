################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/inc" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/CMSIS/core" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/CMSIS/device" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/HAL_Driver/Inc/Legacy" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


