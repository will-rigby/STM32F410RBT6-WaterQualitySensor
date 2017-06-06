/*
 * stm32f410_rtc.h
 *
 *  Created on: 24 May 2017
 *      Author: william.rigby
 */

#ifndef STM32F410_RTC_H_
#define STM32F410_RTC_H_
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* External Function Prototypes */
extern void stm32f410_rtc_init(void);
extern void stm32f410_rtc_program_wakeup(uint16_t delay);
extern void stm32f410_rtc_enter_stop(void);
extern void stm32f410_rtc_exit_stop(void);




#endif /* STM32F410_RTC_H_ */
