/**
 ******************************************************************************
 * @file    stm32f410_fault_indicator.h
 * @author  William Rigby
 * @date    220317
 * @brief   UART Functions
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
 */

#ifndef STM32F410_FAULT_INDICATOR_H_
#define STM32F410_FAULT_INDICATOR_H_
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Fault_Indicator_Pin GPIO_PIN_4
#define Fault_Indicator_Port GPIOC


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External Function Prototypes */
extern void fault_indicator_init(void);
extern void fault_indicator_flash(uint16_t onTime, uint16_t offTime);
extern void fault_indicator_on(void);
extern void fault_indicator_off(void);




#endif /* STM32F410_FAULT_INDICATOR_H_ */
