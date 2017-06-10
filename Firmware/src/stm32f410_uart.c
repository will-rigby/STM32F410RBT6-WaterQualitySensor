/**
 ******************************************************************************
 * @file    stm32f410_uart_uart.c
 * @author  William Rigby
 * @date    220317
 * @brief   UART Driver
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * sxxxxxx_ledbar_hal_init() – intialise LED Light BAR
 * sxxxxxx_ledbar_hal_write() – set LED Light BAR value
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char receiveBuffer[1000];
uint16_t receiveIndex = 0;
uint16_t retrieveIndex = 0;

char debugBuffer[300];
uint16_t debugReceiveIndex = 0;
uint16_t debugRetrieveIndex = 0;

uint8_t aRxBuffer[1];
uint8_t debugRxBuffer[1];
/* Function Definitions -------------------------------------------------------*/

/* USART1 init function */
extern void stmf410_uart_usart1_init(void) {
	/* Enable USART Clock */
	USART1_CLK_ENABLE()
	;

	/* Configure USART Settings */
	USART1->CR1 &= ~(1 << 12); // Write 0 to M in CR1 to set 8 data bits
	USART1->CR2 &= ~((1 << 13) | (1 << 12)); // Write 00 to STOP[1:0] in CR2 to set 1 stop bit
	USART1->BRR = 64000000 / 115200; // APB2 Clock (MHz) / Baud
	USART1->SR &= ~(1 << 2); // Clear RXNE Flag
	USART1->CR1 |= (1 << 3); // Write 1 to the TE in CR1 to enable transmission
	USART1->CR1 |= (1 << 2); // Write 1 to the RE in CR1 to enable reception
	USART1->CR1 |= (1 << 5); // Enable receive Interrupt
	USART1->CR1 |= (1 << 13); // Write 1 to UE in CR1 to enable USART

	/* Enable GPIO TX/RX clock */
	USART1_TX_GPIO_CLK_ENABLE()
	;
	USART1_RX_GPIO_CLK_ENABLE()
	;

	/* Configure GPIO Pins for USART */
	GPIOB->MODER |= (1 << 13); // Set Mode to AF
	GPIOB->MODER &= ~(1 << 12); // Set Mode to AF
	GPIOB->OTYPER &= ~(1 << 6); // Set to Push Pull
	GPIOB->PUPDR |= (1 << 12); // Set Pull Up
	GPIOB->PUPDR &= ~(1 << 13); // Set no Pull Down
	GPIOB->AFR[0] |= (1 << 24) | (1 << 25) | (1 << 26); // Set to AF7 USART1
	GPIOB->AFR[0] &= ~(1 < 27); // Set to AF7 USART1
	GPIOB->OSPEEDR |= (1<<12)|(1 << 13); // Set Speed High

	GPIOB->MODER |= (1 << 15); // Set Mode to AF
	GPIOB->MODER &= ~(1 << 14); // Set Mode to AF
	GPIOB->OTYPER |= (1 << 7); // Set to Open Drain
	GPIOB->PUPDR |= (1 << 14); // Set Pull Up
	GPIOB->PUPDR &= ~(1 << 15); // Set no Pull Down
	GPIOB->AFR[0] |= (1 << 28) | (1 << 29) | (1 << 30); // Set to AF7 USART1
	GPIOB->AFR[1] &= ~(1 < 31); // Set to AF7 USART1
	GPIOB->OSPEEDR |= (1<<14)|(1 << 15); // Set Speed High

	/* NVIC for USART */
//#ifdef USART_INTERRUPT_ENABLED
	NVIC_ClearPendingIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, 2);
	NVIC_SetVector(USART1_IRQn, (uint32_t)&stm32f410_uart_usart1_receive);
	NVIC_EnableIRQ(USART1_IRQn);
//#endif
}

/* USART2 init function */
extern void stmf410_uart_usart2_init(void) {
	/* Enable USART Clock */
	USART2_CLK_ENABLE()
	;

	/* Configure USART Settings */
	USART2->CR1 &= ~(1 << 12); // Write 0 to M in CR1 to set 8 data bits
	USART2->CR2 &= ~((1 << 13) | (1 << 12)); // Write 00 to STOP[1:0] in CR2 to set 1 stop bit
	USART2->BRR = 32000000 / 115200; // APB1 Clock (MHz) / Baud
	USART2->SR &= ~(1 << 5); // Clear RXNE Flag
	USART2->CR1 |= (1 << 3); // Write 1 to the TE in CR1 to enable transmission
	USART2->CR1 |= (1 << 2); // Write 1 to the RE in CR1 to enable reception
	USART2->CR1 |= (1 << 5); // Enable receive Interrupt
	USART2->CR1 |= (1 << 13); // Write 1 to UE in CR1 to enable USART

	/* Enable GPIO TX/RX clock */
	USART2_TX_GPIO_CLK_ENABLE()
	;
	USART2_RX_GPIO_CLK_ENABLE()
	;

	/* Configure GPIO Pins for USART */
	GPIOA->MODER |= (1 << 5); // Set Mode to AF
	GPIOA->MODER &= ~(1 << 4); // Set Mode to AF
	GPIOA->OTYPER &= ~(1 << 2); // Set to Push Pull
	GPIOA->PUPDR |= (1 << 4); // Set Pull Up
	GPIOA->PUPDR &= ~(1 << 5); // Set no Pull Down
	GPIOA->AFR[0] |= (1 << 8) | (1 << 9) | (1 << 10); // Set to AF7 USART1
	GPIOA->AFR[0] &= ~(1 < 11); // Set to AF7 USART1
	GPIOA->OSPEEDR |= (1 << 3); // Set Speed High

	GPIOA->MODER |= (1 << 7); // Set Mode to AF
	GPIOA->MODER &= ~(1 << 6); // Set Mode to AF
	GPIOA->OTYPER |= (1 << 3); // Set to Open Drain
	GPIOA->PUPDR |= (1 << 6); // Set Pull Up
	GPIOA->PUPDR &= ~(1 << 7); // Set no Pull Down
	GPIOA->AFR[0] |= (1 << 12) | (1 << 13) | (1 << 14); // Set to AF7 USART1
	GPIOA->AFR[1] &= ~(1 < 15); // Set to AF7 USART1
	GPIOA->OSPEEDR |= (1 << 5); // Set Speed High

//#ifdef USART_INTERRUPT_ENABLED
	/* NVIC for USART */
	NVIC_ClearPendingIRQ(USART2_IRQn);
	NVIC_SetPriority(USART2_IRQn, 3);
	NVIC_SetVector(USART2_IRQn, (uint32_t)&stm32f410_uart_usart2_receive);
	NVIC_EnableIRQ(USART2_IRQn);
//#endif
}

extern void stm32f410_uart_usart1_transmit(char* message) {
	int i = 0;
	while (message[i]) {
		/* Wait until TXE is set */
		while (!(USART1->SR & (1 << 7)))
			;
		/* Transfer data to Data register */
		USART1->DR = message[i];
		i++;
	}
}

extern void stm32f410_uart_usart1_receive(void) {
	/* if RXNE in SR is set, data in buffer */
	if (USART1->SR & (1 << 5)) {
		/* Retrieve Data */
		receiveBuffer[receiveIndex] = USART1->DR;
		receiveIndex++;
		if (receiveIndex == 1000) {
			receiveIndex = 0;
		}

		/* Reset Receive Data Flag */
		USART1->SR &= ~(1 << 2);
		NVIC_ClearPendingIRQ(USART1_IRQn);
	}
}

extern void stm32f410_uart_usart2_transmit(char* message) {
	int i = 0;
	while (message[i]) {
		/* Wait until TXE is set */
		while (!(USART2->SR & (1 << 7)))
			;
		/* Transfer data to Data register */
		USART2->DR = message[i];
		i++;
	}
}

extern void stm32f410_uart_usart2_receive(void) {
	/* if RXNE in SR is set, data in buffer */
	if (USART2->SR & (1 << 5)) {
		/* Retrieve Data */
		debugBuffer[debugReceiveIndex] = USART2->DR;
		debugReceiveIndex++;
		if (debugReceiveIndex == 300) {
			debugReceiveIndex = 0;
		}

		/* Reset Receive Data Flag */
		USART2->SR &= ~(1 << 5);
		NVIC_ClearPendingIRQ(USART2_IRQn);
	}
}

extern uint16_t stm32f410_uart_check_usart1_status(void) {
	return receiveIndex - retrieveIndex;
}

extern uint16_t stm32f410_uart_check_usart2_status(void) {
	return debugReceiveIndex - debugRetrieveIndex;
}

extern char stm32f410_uart_usart1_get_char(void) {
	char character = receiveBuffer[retrieveIndex];
	retrieveIndex++;
	if (retrieveIndex == 1000) {
		retrieveIndex = 0;
	}
	return character;
}

extern char stm32f410_uart_usart2_get_char(void) {
	char character = debugBuffer[debugRetrieveIndex];
	debugRetrieveIndex++;
	if (debugRetrieveIndex == 300) {
		debugRetrieveIndex = 0;
	}
	return character;
}

extern void stm32f410_uart_get_usart1_reply(char* replyBuffer, uint16_t replyLength) {
	uint16_t i = 0;
	memset(replyBuffer, 0, replyLength);
	while (stm32f410_uart_check_usart1_status()) {
		replyBuffer[i] = stm32f410_uart_usart1_get_char();
		i++;
		if (i == replyLength - 1) {
			break;
		}
	}
}

extern void stm32f410_uart_get_usart2_reply(char* replyBuffer, uint16_t replyLength) {
	uint16_t i = 0;
	memset(replyBuffer, 0, replyLength);
	while (stm32f410_uart_check_usart2_status()) {
		replyBuffer[i] = stm32f410_uart_usart2_get_char();
		i++;
		if (i == replyLength - 1) {
			break;
		}
	}
}

void USART1_IRQHandler(void) {
	stm32f410_uart_usart1_receive();
	return;

	//HAL_UART_IRQHandler(&sim5320aUART);

}

/**
 * @brief This function handles USART2 global interrupt.
 */
void USART2_IRQHandler(void) {
	stm32f410_uart_usart1_receive();
	return;

	//HAL_UART_IRQHandler(&debugUART);

}
