/**
 ******************************************************************************
 * @file    stm32f410_fault_indicator.c
 * @author  William Rigby
 * @date    220317
 * @brief   Drives the Fault Indicator LED
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************

 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_fault_indicator.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Function Definitions -------------------------------------------------------*/
extern void fault_indicator_init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;

	/*Configure GPIO pin :  */
	GPIOA->MODER &= ~(0b1<<8);
	GPIOB->OTYPER &= ~(1 << 4); // Set to Push Pull
	GPIOB->PUPDR &= ~((1 << 8) | (1 << 9)); // Set No Pull (Pull down Resistor on LED
	GPIOB->OSPEEDR |= (1 << 9); // Set Speed High

	GPIOA->ODR &= ~(1 << 4);
}

extern void fault_indicator_flash(uint16_t onTime, uint16_t offTime) {
	while (1) {
		fault_indicator_on();
		HAL_Delay(onTime);
		fault_indicator_off();
		HAL_Delay(offTime);
	}
}

extern void fault_indicator_on(void) {
	GPIOA->ODR |= (1 << 4);
}

extern void fault_indicator_off(void){
	GPIOA->ODR &= ~(1 << 4);
}
