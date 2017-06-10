/**
 ******************************************************************************
 * @file    stm32f410_uart.h
 * @author  William Rigby
 * @date    220317
 * @brief   UART Functions
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************

 ******************************************************************************
 */
#ifndef STM32F410_ATLAS_SCIENTIFIC_H_
#define STM32F410_ATLAS_SCIENTIFIC_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f410_i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* External Function Prototypes */
extern void stm32f410_as_read_pH(char* buffer, uint8_t bufferLength);
extern void stm32f410_as_read_conductivity(char* buffer, uint8_t bufferLength);
extern void stm32f410_as_temp_calib_pH(char* temperature, uint8_t bufferLength);
extern void stm32f410_as_temp_calib_conductivity(char* temperature, uint8_t bufferLength);
extern void stm32f410_as_pH_sleep(void);
extern void stm32f410_as_conductivity_sleep(void);


#endif /* STM32F410_ATLAS_SCIENTIFIC_H_ */
