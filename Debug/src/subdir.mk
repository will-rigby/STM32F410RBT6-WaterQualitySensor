################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cmsis_nvic.c \
../src/main.c \
../src/stm32f410_1wire.c \
../src/stm32f410_atlas_scientific.c \
../src/stm32f410_fault_indicator.c \
../src/stm32f410_i2c.c \
../src/stm32f410_rtc.c \
../src/stm32f410_sim5320a.c \
../src/stm32f410_uart.c \
../src/stm32f410_ultrasonic_rangefinder.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/cmsis_nvic.o \
./src/main.o \
./src/stm32f410_1wire.o \
./src/stm32f410_atlas_scientific.o \
./src/stm32f410_fault_indicator.o \
./src/stm32f410_i2c.o \
./src/stm32f410_rtc.o \
./src/stm32f410_sim5320a.o \
./src/stm32f410_uart.o \
./src/stm32f410_ultrasonic_rangefinder.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/cmsis_nvic.d \
./src/main.d \
./src/stm32f410_1wire.d \
./src/stm32f410_atlas_scientific.d \
./src/stm32f410_fault_indicator.d \
./src/stm32f410_i2c.d \
./src/stm32f410_rtc.d \
./src/stm32f410_sim5320a.d \
./src/stm32f410_uart.d \
./src/stm32f410_ultrasonic_rangefinder.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4 -DSTM32F410RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F410Rx -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/inc" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/CMSIS/core" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/CMSIS/device" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/HAL_Driver/Inc/Legacy" -I"F:/Dropbox/University/METR4901/Australia/workspace/STM32F410RBT6HAL/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


