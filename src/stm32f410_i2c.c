/**
 ******************************************************************************
 * @file    stm32f410_i2c.c
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
#include "stm32f410_i2c.h"
#include "stm32f410_uart.h"
#include "stm32f410_1wire.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private Function Definitions */
uint8_t started = 0;
extern void stm32f410_i2c_init(void) {

	__HAL_RCC_FMPI2C1_CLK_ENABLE()
	;
	/*
	 hfmpi2c1.Instance = FMPI2C1;
	 hfmpi2c1.Init.Timing = 0x00707CBB;
	 hfmpi2c1.Init.OwnAddress1 = 0;
	 hfmpi2c1.Init.AddressingMode = FMPI2C_ADDRESSINGMODE_7BIT;
	 hfmpi2c1.Init.DualAddressMode = FMPI2C_DUALADDRESS_DISABLE;
	 hfmpi2c1.Init.OwnAddress2 = 0;
	 hfmpi2c1.Init.OwnAddress2Masks = FMPI2C_OA2_NOMASK;
	 hfmpi2c1.Init.GeneralCallMode = FMPI2C_GENERALCALL_DISABLE;
	 hfmpi2c1.Init.NoStretchMode = FMPI2C_NOSTRETCH_DISABLE;
	 HAL_FMPI2C_Init(&hfmpi2c1);
	 */

	/* Disable PE Bit */
	FMPI2C1->CR1 &= ~(1);
	FMPI2C1->CR1 |= (1 << 17); // CLock Stretching Disabled

	/* Configure Timing Register */
	FMPI2C1->TIMINGR = 0x00707CBB;

	/* Configure Control Register 1 */
	/* Reset values are satisfactory */

	/* Configure Control Register 2 */
	FMPI2C1->CR2 &= ~(1 << 11); // 7 Bit Address Mode

	/* Enable I2C Bus */
	FMPI2C1->CR1 |= 1;

	//GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE()
	;
	/*
	 GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
	 GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	 GPIO_InitStruct.Alternate = GPIO_AF4_FMPI2C1;
	 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);*/
	/* Configure GPIO Pins for I2C */
	GPIOB->MODER |= (1 << 29); // Set Mode to AF
	GPIOB->MODER &= ~(1 << 28); // Set Mode to AF
	GPIOB->OTYPER |= (1 << 14); // Set to Open Drain
	GPIOB->PUPDR &= ~(1 << 28); // Set no Pull Up
	GPIOB->PUPDR &= ~(1 << 29); // Set no Pull Down
	GPIOB->AFR[1] |= (1 << 26); // Set to AF7 USART1
	GPIOB->AFR[1] &= ~((1 << 24) | (1 << 25) | (1 < 27)); // Set to AF4 USART1
	GPIOB->OSPEEDR |= (1 << 28) | (1 << 29); // Set Speed High

	GPIOB->MODER |= (1 << 31); // Set Mode to AF
	GPIOB->MODER &= ~(1 << 30); // Set Mode to AF
	GPIOB->OTYPER |= (1 << 15); // Set to Open Drain
	GPIOB->PUPDR &= ~(1 << 30); // Set no Pull Up
	GPIOB->PUPDR &= ~(1 << 31); // Set no Pull Down
	GPIOB->AFR[1] |= (1 << 30); // Set to AF7 USART1
	GPIOB->AFR[1] &= ~((1 << 28) | (1 << 29) | (1 < 31)); // Set to AF4 USART1
	GPIOB->OSPEEDR |= (1 << 30) | (1 << 31); // Set Speed High

}

extern void stm32f410_i2c_write_bytes(uint8_t address, uint8_t* reg,
		uint8_t numberOfBytes) {
	uint8_t i = 0;
	while (FMPI2C1->ISR & (1 << 15))
		;
	FMPI2C1->CR2 &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20)
			| (1 << 21) | (1 << 22) | (1 << 23)); // Reset N-Bytes
	FMPI2C1->CR2 |= (numberOfBytes << 16); // Set N-Bytes
	FMPI2C1->CR2 &= ~(1 << 25); //Auto End Mode OFF
	FMPI2C1->CR2 &= ~(0x3FF); // Clear Slave Address Bits
	FMPI2C1->CR2 |= address & (0b11111110); // Set Slave Address Bits
	FMPI2C1->CR2 &= ~(1 << 10); // Set to Write
	FMPI2C1->CR2 |= (1 << 13); // Generate Start Condition on first byte transfer

	/* Transfer all bytes but last */
	while (numberOfBytes > 1) {
		while (!(FMPI2C1->ISR & 1)) { // While Byte not sent
			if (FMPI2C1->CR2 & (1 << 14)) {
				FMPI2C1->CR2 &= ~(1 << 14);
				//NACK Received;
				return;
			}
		}
		FMPI2C1->TXDR = reg[i]; // Send Byte
		i++;
		numberOfBytes--;
	}
	/* Transfer Last Byte */
	while (!(FMPI2C1->ISR & 1)) { // While Byte not sent
		if (FMPI2C1->CR2 & (1 << 14)) {
			FMPI2C1->CR2 &= ~(1 << 14);
			//NACK Received;
			return;
		}
	}

	FMPI2C1->CR2 |= (1 << 14); // Set Stop Flag so stop condition is generated after byte
	FMPI2C1->TXDR = reg[i]; // Send Byte
}

extern void stm32f410_i2c_read_bytes(uint8_t address, uint8_t* reg,
		uint8_t numberOfBytes) {
	uint8_t i = 0;
	while (FMPI2C1->ISR & (1 << 15))
		;
	FMPI2C1->CR2 &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20)
			| (1 << 21) | (1 << 22) | (1 << 23)); // Reset N-Bytes
	FMPI2C1->CR2 |= (numberOfBytes << 16); // Set N-Bytes
	FMPI2C1->CR2 |= (1 << 25); //Auto End Mode OFF
	FMPI2C1->CR2 &= ~(0x3FF); // Clear Slave Address Bits
	FMPI2C1->CR2 |= address & (0b11111110); // Set Slave Address Bits
	FMPI2C1->CR2 |= (1 << 10); // Set to Write
	FMPI2C1->CR2 |= (1 << 13); // Generate Start Condition on first byte transfer
	while (!(FMPI2C1->ISR & (1 << 2))) {
		reg[i] = FMPI2C1->RXDR;
		i++;
		if (!(FMPI2C1->ISR & (1 << 6)) || (i == numberOfBytes)) {
			break;
		}
	}

}

extern void stm32f410_i2c_bitbang_init(void) {
	FMPI2C1->CR1 &= ~(1);
	GPIOB->MODER |= (1 << 28); // Set Mode to Output
	GPIOB->MODER &= ~(1 << 29); // Set Mode to Output
	GPIOB->OTYPER &= ~(1 << 14); // Set to Open Drain
	GPIOB->PUPDR &= ~(1 << 28); // Set no Pull Up
	GPIOB->PUPDR &= ~(1 << 29); // Set no Pull Down
	GPIOB->OSPEEDR |= (1 << 28) | (1 << 29); // Set Speed High
	GPIOB->ODR |= (1 << 14);

	GPIOB->MODER |= (1 << 30); // Set Mode to Output
	GPIOB->MODER &= ~(1 << 31); // Set Mode to Output
	GPIOB->OTYPER &= ~(1 << 15); // Set to Open Drain
	GPIOB->PUPDR &= ~(1 << 30); // Set no Pull Up
	GPIOB->PUPDR &= ~(1 << 31); // Set no Pull Down
	GPIOB->OSPEEDR |= (1 << 30) | (1 << 31); // Set Speed High
	GPIOB->ODR |= (1 << 15);
}

void i2c_delay(void) {
	delay_us(5);
}

void set_SCL_high(void) {
	GPIOB->ODR |= (1 << 15);
}

void set_SCL_low(void) {
	GPIOB->ODR &= ~(1 << 15);
}

void set_SDA_high(void) {
	GPIOB->ODR |= (1 << 14);
}

void set_SDA_low(void) {
	GPIOB->ODR &= ~(1 << 14);
}

uint8_t read_SCL(void) {
	uint8_t returnVal = (uint8_t) (GPIOB->IDR & (1 << 15)) >> 15;
	return returnVal;
}

uint8_t read_SDA(void) {

	uint8_t returnVal = (uint8_t) (GPIOB->IDR & (1 << 14)) >> 14;

	return returnVal;
}

void i2c_start_cond(void) {
	if (started) {
		set_SDA_high();
		i2c_delay();
		set_SCL_high();
		i2c_delay();
		i2c_delay();
	}
	set_SCL_high();
	i2c_delay();
	i2c_delay();
	i2c_delay();
	set_SDA_low();
	i2c_delay();
	set_SCL_low();
	i2c_delay();
	started = 1;
}

void i2c_stop_cond(void) {
	set_SDA_low();
	i2c_delay();
	set_SCL_high();

	i2c_delay();
	set_SDA_high();
	i2c_delay();

	set_SCL_low();
	started = 0;
}

void i2c_write_bit(uint8_t bit) {
	if (bit) {
		set_SDA_high();
	} else {
		set_SDA_low();
	}
	i2c_delay();
	set_SCL_high();
	i2c_delay();
	set_SCL_low();

}

uint8_t i2c_read_bit(void) {
	uint8_t bit;

	set_SDA_high(); // OD Allow Slave to Drive
	i2c_delay();
	set_SCL_high();
	i2c_delay();
	bit = read_SDA();
	set_SCL_low();
	return bit;
}

extern uint8_t stm32f410_i2c_bitbang_write_byte(uint8_t byte, uint8_t sendStart,
		uint8_t sendStop) {
	if (sendStart) {
		i2c_start_cond();
	}
	for (int bit = 0; bit < 8; ++bit) {
		i2c_write_bit((byte & 0x80) != 0);
		byte = byte << 1;
	}

	uint8_t nack = i2c_read_bit();
	if (sendStop) {
		i2c_stop_cond();
	}
	return nack;
}

extern uint8_t stm32f410_i2c_bitbang_read_byte(uint8_t nack, uint8_t sendStop) {
	uint8_t byte;
	GPIOB->MODER &= ~(1 << 28);
	GPIOB->MODER &= ~(1 << 29);
	for (int bit = 0; bit < 8; ++bit) {
		byte = (byte << 1) | i2c_read_bit();
	}
	GPIOB->MODER |= (1 << 28);
	GPIOB->MODER &= ~(1 << 29);
	i2c_write_bit(nack);
	if (sendStop) {
		i2c_stop_cond();
	}

	return byte;
}

extern void stm32f410_i2c_bitbang_write_bytes(uint8_t address,
		uint8_t* byteBuffer, uint8_t numberOfBytes) {
	address = (address << 1) & (~1);
	stm32f410_i2c_bitbang_write_byte(address, 1, 0);
	uint i = 0;
	for (i = 0; i < numberOfBytes - 1; i++) {
		if (stm32f410_i2c_bitbang_write_byte(byteBuffer[i], 0, 0)) {
			break;
		}
	}
	stm32f410_i2c_bitbang_write_byte(byteBuffer[i], 0, 1);
}

extern void stm32f410_i2c_bitbang_read_bytes(uint8_t address,
		uint8_t* byteBuffer, uint8_t numberOfBytes) {
	address = (address << 1) | 1;
	stm32f410_i2c_bitbang_write_byte(address, 1, 0);
	uint i = 0;
	for (i = 0; i < numberOfBytes - 1; i++) {
		byteBuffer[i] = stm32f410_i2c_bitbang_read_byte(0, 0);
	}
	byteBuffer[i] = stm32f410_i2c_bitbang_read_byte(1, 1);
}

