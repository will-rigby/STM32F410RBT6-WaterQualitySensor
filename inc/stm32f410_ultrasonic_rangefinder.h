/**
 ******************************************************************************
 * @file    stm32f410_ultrasonic_rangefinder.h
 * @author  William Rigby
 * @date    220317
 * @brief   Functions for interfacing with the ultrasonic rangefinder using analog to digital conversion
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * MX_ADC1_Init() - Initialise First ADC
 * MX_ADC2_Init() - Initialise Second ADC
 * read_conductivity_adc() - Reads the ADC connected to the conductivity sensor
 * read_ph_adc() - Reads the ADC connected to the pH sensor
 * read_ultrasonic_adc() - Reads the ADC connected to the ultrasonic rangefinder
 ******************************************************************************
 *******************************************************************************/
#ifndef STM32F410_ULTRASONIC_RANGEFINDER_H_
#define STM32F410_ULTRASONIC_RANGEFINDER_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f410_fault_indicator.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Ultrasonic_Power_Pin GPIO_PIN_8
#define Ultrasonic_Power_Pin_GPIO_Port GPIOC
#define ADC1_CLK_ENABLE() __HAL_RCC_ADC1_CLK_ENABLE()
#define ADC1_CHANNEL12_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define Ultrasonic_Power_Pin_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef rangeFinderAdc;

/* External Function Prototypes */

extern void ultrasonic_rangefinder_init(void);
extern uint16_t read_ultrasonic_adc(void);


#endif /* STM32F410_ULTRASONIC_RANGEFINDER_H_ */
