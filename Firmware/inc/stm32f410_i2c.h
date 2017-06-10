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
#ifndef STM32F410_I2C_H_
#define STM32F410_I2C_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_fmpi2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* External Function Prototypes */
extern void stm32f410_i2c_init(void);
extern void stm32f410_i2c_write_bytes(uint8_t address, uint8_t* reg,
		uint8_t numberOfBytes);
extern void stm32f410_i2c_read_bytes(uint8_t address, uint8_t* reg,
		uint8_t numberOfBytes);
extern void stm32f410_i2c_bitbang_init(void);
void i2c_delay(void);
void set_SCL_high(void);
void set_SCL_low(void);
void set_SDA_high(void);
void set_SDA_low(void);
uint8_t read_scl(void);
uint8_t read_SDA(void);
void i2c_start_cond(void);
void i2c_stop_condition(void);
void i2c_write_bit(uint8_t bit);
uint8_t i2c_read_bit(void);
extern uint8_t stm32f410_i2c_bitbang_write_byte(uint8_t byte, uint8_t sendStart,
		uint8_t sendStop);
extern uint8_t stm32f410_i2c_bitbang_read_byte(uint8_t nack, uint8_t sendStop);
extern void stm32f410_i2c_bitbang_write_bytes(uint8_t address,
		uint8_t* byteBuffer, uint8_t numberOfBytes);
extern void stm32f410_i2c_bitbang_read_bytes(uint8_t address,
		uint8_t* byteBuffer, uint8_t numberOfBytes);
#endif /* STMF32410_I2C_H_ */
