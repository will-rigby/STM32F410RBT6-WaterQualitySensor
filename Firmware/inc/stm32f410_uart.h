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
#ifndef STM32F410_UART_H_
#define STM32F410_UART_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_nvic.h"
#include "stm32f410_fault_indicator.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Definition for USART1 clock resources */
#define USART1_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
#define USART1_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USART1_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

/* Definition for USART2 clock resources */
#define USART2_CLK_ENABLE() __HAL_RCC_USART2_CLK_ENABLE()
#define USART2_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART2_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* External Function Prototypes */
extern void stmf410_uart_usart1_init(void);
extern void stmf410_uart_usart2_init(void);
extern void stm32f410_uart_usart1_transmit(char* message);
extern void stm32f410_uart_usart1_receive(void);
extern void stm32f410_uart_usart2_transmit(char* message);
extern void stm32f410_uart_usart2_receive(void);
extern uint16_t stm32f410_uart_check_usart1_status(void);
extern uint16_t stm32f410_uart_check_usart2_status(void);
extern char stm32f410_uart_usart1_get_char(void);
extern char stm32f410_uart_usart2_get_char(void);
extern void stm32f410_uart_get_usart1_reply(char* replyBuffer, uint16_t replyLength);
extern void stm32f410_uart_get_usart2_reply(char* replyBuffer, uint16_t replyLength);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);


#endif /* STM32F410_UART_H_ */
