/**
 ******************************************************************************
 * @file    stm32f410_atlas_scientific.c
 * @author  William Rigby
 * @date    220317
 * @brief   i2c driver
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * sxxxxxx_ledbar_hal_init() – intialise LED Light BAR
 * sxxxxxx_ledbar_hal_write() – set LED Light BAR value
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_atlas_scientific.h"
#include "stm32f410_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private Function Definitions */
extern void stm32f410_as_read_pH(char* buffer, uint8_t bufferLength) {
	uint8_t read = (uint8_t) 'r';
	stm32f410_i2c_bitbang_write_bytes(0x63, &read, 1);
	HAL_Delay(1200);
	stm32f410_i2c_bitbang_read_bytes(0x63, (uint8_t*) buffer, bufferLength);
	for (uint8_t i = 0; i < bufferLength - 1; i++) {
		buffer[i] = buffer[i + 1];
	}
}

extern void stm32f410_as_read_conductivity(char* buffer, uint8_t bufferLength) {
	uint8_t read = (uint8_t) 'r';
	stm32f410_i2c_bitbang_write_bytes(0x64, &read, 1);
	HAL_Delay(1200);
	stm32f410_i2c_bitbang_read_bytes(0x64, (uint8_t*) buffer, bufferLength);
	for (uint8_t i = 0; i < bufferLength - 1; i++) {
		buffer[i] = buffer[i + 1];
	}

	for (uint8_t i = 0; i < bufferLength; i++) {
		if(buffer[i] == ','){
			for(uint8_t j = i; j<bufferLength;j++){
				buffer[j] = 0;
			}
			break;
		}
	}

}

extern void stm32f410_as_pH_sleep(void) {
	stm32f410_i2c_bitbang_write_bytes(0x63, (uint8_t*) "Sleep", 5);
}

extern void stm32f410_as_conductivity_sleep(void) {
	stm32f410_i2c_bitbang_write_bytes(0x64, (uint8_t*) "Sleep", 5);
}

