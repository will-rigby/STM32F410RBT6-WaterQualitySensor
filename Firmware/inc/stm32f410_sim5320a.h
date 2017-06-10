/**
 ******************************************************************************
 * @file    stm32f410_sim5320a.h
 * @author  William Rigby
 * @date    220317
 * @brief   Functions for interfacing with the SimComm SIM5320A 3G cellular module
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * sim5320a_check_status() - Transmits an "AT" to and determines the reply
 * sim5320a_init() initialises the pins for the interfacing with the SIM5320A
 * sim5320a_activate() - turns the SIM5320a and ensures whether it is functioning correctly
 * sim5320a_set_default_parameters() - sets the TCP/IP address of the server, apn of the data network and the mobile number to send texts to
 * sim5320a_activate_sms() - activates the SMS functionality of the SIM5320a
 * sim5320a_send_text_message() sends the data in a text message to the specified number
 * sim5320a_connect_to_tcp_server() - attempts to activate data network and connect to the specified TCP server
 * sim5320a_tcp_send_data() - if connected to a TCP server it will attempt to send the data over TCP packets
 * sim5320a_close_tcp_connection() - closes the current TCP connection
 * sim5320a_power_off() - turns off the SIM5320a
 * sim5320a_power_on() - turns on the SIM5320a
 * sim5320a_signal_quality() - polls the SIM5320a for the current mobile signal quality in dB
 * sim5320a_battery_percent() - polls the SIM5320a for the battery charge in percent
 * simg4320a_check_text_messages() - checks the SIM5320a for SMS messages and retrieves them
 ******************************************************************************
 */

#ifndef STM32F410_SIM5320A_H_
#define STM32F410_SIM5320A_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_uart.h"
#include <string.h>
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* GPIO Pin Definitions */
#define Power_Status_Pin GPIO_PIN_0
#define Power_Status_GPIO_Port GPIOB
#define PWR_CTRL_Pin GPIO_PIN_12
#define PWR_CTRL_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_13
#define RESET_GPIO_Port GPIOB
#define NETSTATUS_GPIO_PIN GPIO_PIN_2
#define NETSTATUS_GPIO_Port GPIOB

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* TCP and SMS Parameters */


/* External Function Prototypes */
extern uint8_t sim5320a_check_status(void);
extern void sim5320a_init(void);
extern uint8_t sim5320a_activate(void);
extern void sim5320a_set_default_parameters(char* accessPoint, char* port, char* ip);
extern uint8_t sim5320a_activate_sms(void);
extern uint8_t sim5320a_send_text_message(char* mobileNumber, char* data);
extern uint8_t sim5320a_connect_to_tcp_server(void);
extern uint8_t sim5320a_connect_to_udp_server(void);
extern uint8_t sim5320a_tcp_send_data(char* data);
extern uint8_t sim5320a_udp_send_data(char* data);
extern uint8_t sim5320a_close_tcpudp_connection(void);
extern void sim5320a_power_off(void);
extern void sim5320a_power_on(void);
extern uint8_t sim5320a_signal_quality(void);
extern uint8_t sim5320a_battery_percent(void);
extern uint8_t sim5320a_check_sms_messages(char messageBank[5][200]);

#endif /* STM32F410_SIM5320A_H_ */
