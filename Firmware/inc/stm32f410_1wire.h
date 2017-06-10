/**
 ******************************************************************************
 * @file    stm32f410_1wire.h
 * @author  William Rigby
 * @date    220317
 * @brief   Drives the 1wire interface to communicate with the DS18B20 Temperature sensor
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************

 ******************************************************************************
 */

#ifndef STM32F410_1WIRE_H_
#define STM32F410_1WIRE_H_

#include "stm32f4xx_hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DS18B20_Pin GPIO_PIN_8
#define DS18B20_GPIO_Port GPIOA

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef oneWireTimer;
/* External Function Prototypes */
extern void oneWire_init(void);
void delay_us(uint16_t microseconds);
void write_bit(uint8_t bit);
void onewire_write_byte(uint8_t byte);
uint8_t onewire_read_byte(void);
extern uint8_t onewire_reset(void);
extern float onewire_read_ds18b20_temp(void);
extern void onewire_read_ds18b20_temp_int16(int16_t intAndDec[2]);
void delay_1us(void);
void delay_5us(void);
void delay_10us(void);
void delay_100us(void);
void oneWire_set_pin_input(void);
void oneWire_set_pin_output(void);


#endif /* STM32F410_1WIRE_H_ */
