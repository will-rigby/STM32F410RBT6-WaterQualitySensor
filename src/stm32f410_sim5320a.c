/**
 ******************************************************************************
 * @file    stmf410_uart_uart.c
 * @author  William Rigby
 * @date    220317
 * @brief   UART Driver
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_sim5320a.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char defaultMobileNumber[13];
char accessPointName[21];
char defaultPort[6];
char defaultIPAddress[21];

/* Global Flags */
uint8_t tcpConnectionOpen = 0; // Keeps track of whether the TCP connection is open
/* Function Definitions -------------------------------------------------------*/
extern uint8_t sim5320a_check_status(void) {
	char reply[60];
	uint8_t replyLength = 60;
	stm32f410_uart_get_usart1_reply(reply, replyLength); // Clear reply buffer
	stm32f410_uart_get_usart1_reply(reply, replyLength); // Clear reply buffer
	stm32f410_uart_usart1_transmit("AT\r\n");

	HAL_Delay(50);
	stm32f410_uart_get_usart1_reply(reply, replyLength);
	stm32f410_uart_usart1_transmit("Reply:");
	stm32f410_uart_usart1_transmit(reply);
	for (uint i = 0; i < (replyLength - 4); i++) {
		if (reply[i] == '\r' && reply[i+1] == '\n' && reply[i+2] == 'O'
				&& reply[i+3] == 'K') {
			return (uint8_t) 0;
		}
	}
	return (uint8_t) 1;
}

extern void sim5320a_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, PWR_CTRL_Pin | RESET_Pin, GPIO_PIN_SET);

	/*Configure GPIO pins : Power_Status_Pin PB1 */
	GPIO_InitStruct.Pin =
	Power_Status_Pin | GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PWR_CTRL_Pin */
	GPIO_InitStruct.Pin = PWR_CTRL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(PWR_CTRL_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : RESET_Pin */
	GPIO_InitStruct.Pin = RESET_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RESET_GPIO_Port, &GPIO_InitStruct);

}

extern uint8_t sim5320a_activate(void) {
	/* Make sure Reset Pin isn't held down */
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 1);

	HAL_Delay(10000);

	/* Wait until Connected to the network - this can take 50 seconds*/
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
		; // Wait until Netstat pin on
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)
		; // Wait until it begins flashing

	/* Reset to factory settings */
	stm32f410_uart_usart1_transmit("ATZ\r\n");
	HAL_Delay(100);

	/* Turn Off Command Echo */
	stm32f410_uart_usart1_transmit("ATE0\r\n");

	HAL_Delay(50);

	/* Check if OKAY*/
	return sim5320a_check_status(); // 0 = PASS
}

extern void sim5320a_set_default_parameters(char* accessPoint, char* port,
		char* ip) {

	sprintf(accessPointName, "%s", accessPoint);
	sprintf(defaultPort, "%s", port);
	sprintf(defaultIPAddress, "%s", ip);

}

extern uint8_t sim5320a_activate_sms(void) {

	char reply[60];
	uint16_t replyLength = 60;

	/* AT+CMGF=1 Select SMS message format as text mode */
	stm32f410_uart_usart1_transmit("AT+CMGF=1\r\n");
	HAL_Delay(80);
	stm32f410_uart_get_usart1_reply(reply, replyLength);
	if (strstr("OK\r\n", reply) == NULL) {
		return 1;
	}

	return 0;
}

extern uint8_t sim5320a_send_text_message(char* mobileNumber, char* data) {
	char message[80]; // buffer to store message

	/* AT+CMGS - Send Message */
	sprintf(message, "AT+CMGS=\"%s\"\r\n", mobileNumber);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(50);

	/* Send data itself followed by newline and then CTRL+Z character */
	char ctrlz = 26;
	sprintf(message, "%s\r\n%c\r\n", data, ctrlz);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(5000);

	return 0;
}

extern uint8_t sim5320a_connect_to_tcp_server(void) {
	if (tcpConnectionOpen == 0) {
		char message[80]; // buffer to store message
		char reply[80];
		uint16_t replyLength = 80;

		/* Define socket PDP context */
		sprintf(message, "AT+CGSOCKCONT=1,\"IP\",\"%s\"\r\n", accessPointName);
		stm32f410_uart_get_usart1_reply(reply, replyLength); // Clear Input Buffer
		stm32f410_uart_usart1_transmit(message);
		HAL_Delay(100);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[0] == '\r' && reply[1] == '\n' && reply[2] == 'O'
				&& reply[3] == 'K') == 0) {
			return (uint8_t) 1; // AT+CGSOCKCONT=1 Failed
		}

		/* Set TCP/IP Application Mode */
		stm32f410_uart_usart1_transmit("AT+CIPMODE=0\r\n");
		HAL_Delay(15);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[0] == '\r' && reply[1] == '\n' && reply[2] == 'O'
				&& reply[3] == 'K') == 0) {
			return (uint8_t) 2; // AT+CIPMODE=0 Failed
		}

		/* Start Data Network */
		stm32f410_uart_usart1_transmit("AT+NETOPEN\r\n");
		HAL_Delay(5000);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[9] == 'N' && reply[10] == 'E' && reply[11] == 'T'
				&& reply[12] == 'O' && reply[13] == 'P' && reply[14] == 'E'
				&& reply[15] == 'N' && reply[18] == '0') == 0) {
			return (uint8_t) 3; // NETOPEN Failed
		}

		/* Open TCP Connection to server */
		sprintf(message, "AT+CIPOPEN=0,\"TCP\",\"%s\",%s\r\n", defaultIPAddress,
				defaultPort);
		stm32f410_uart_usart1_transmit(message);
		HAL_Delay(1000);

	}
	/* Set internal flag to open */
	tcpConnectionOpen = 1;

	return 0;

}

extern uint8_t sim5320a_connect_to_udp_server(void) {
	if (tcpConnectionOpen == 0) {
		char message[80]; // buffer to store message
		char reply[80];
		uint16_t replyLength = 80;

		/* Define socket PDP context */
		sprintf(message, "AT+CGSOCKCONT=1,\"IP\",\"telstra.wap\"\r\n");
		stm32f410_uart_get_usart1_reply(reply, replyLength); // Clear Input Buffer
		/*stm32f410_uart_usart1_transmit("AT+CGSOCKCONT=1,\"IP\",\"");
		 stm32f410_uart_usart1_transmit()*/
		HAL_Delay(100);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[0] == '\r' && reply[1] == '\n' && reply[2] == 'O'
				&& reply[3] == 'K') == 0) {
			return (uint8_t) 1; // AT+CGSOCKCONT=1 Failed
		}

		/* Set TCP/IP Application Mode */
		stm32f410_uart_usart1_transmit("AT+CIPMODE=0\r\n");
		HAL_Delay(15);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[0] == '\r' && reply[1] == '\n' && reply[2] == 'O'
				&& reply[3] == 'K') == 0) {
			return (uint8_t) 2; // AT+CIPMODE=0 Failed
		}

		/* Start Data Network */
		stm32f410_uart_usart1_transmit("AT+NETOPEN\r\n");
		HAL_Delay(5000);
		stm32f410_uart_get_usart1_reply(reply, replyLength);
		if ((reply[9] == 'N' && reply[10] == 'E' && reply[11] == 'T'
				&& reply[12] == 'O' && reply[13] == 'P' && reply[14] == 'E'
				&& reply[15] == 'N' && reply[18] == '0') == 0) {
			return (uint8_t) 3; // NETOPEN Failed
		}

		/* Open TCP Connection to server */
		sprintf(message, "AT+CIPOPEN=0,\"UDP\",,,8080\r\n");
		stm32f410_uart_usart1_transmit(message);
		HAL_Delay(1000);

	}
	/* Set internal flag to open */
	tcpConnectionOpen = 1;

	return 0;

}

extern uint8_t sim5320a_tcp_send_data(char* data) {
	char message[120]; // buffer to store message
	uint8_t messageLength = 120; // length of data

	sprintf(message, "AT+CIPSEND=0,%d\r\n", messageLength);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(100);

	sprintf(message, "%s", data);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(500);

	return 0;
}

extern uint8_t sim5320a_udp_send_data(char* data) {
	char message[120]; // buffer to store message
	uint8_t messageLength = 120; // length of data

	sprintf(message, "AT+CIPSEND=0,%d,\"125.168.189.226\",4523\r\n",
			messageLength);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(100);

	sprintf(message, "%s", data);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(500);

	return 0;
}

extern uint8_t sim5320a_close_tcpudp_connection(void) {
	if (tcpConnectionOpen) {
		stm32f410_uart_usart1_transmit("AT+CIPCLOSE=0\r\n");
		HAL_Delay(600);

		stm32f410_uart_usart1_transmit("AT+NETCLOSE\r\n");
		HAL_Delay(100);

	}
	/* Set internal flag to closed */
	tcpConnectionOpen = 0;

	return 0;
}

extern void sim5320a_power_off(void) {
	uint16_t tick = HAL_GetTick() + 1000;
	uint8_t status = 0;
	while (HAL_GetTick() < tick) {
		status = status | HAL_GPIO_ReadPin(NETSTATUS_GPIO_Port,
		NETSTATUS_GPIO_PIN);
	}

	if (status) {
		HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, 0);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, 1);
	}
}

extern void sim5320a_power_on(void) {
	/* Make sure Reset Pin isn't held down */
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 1);
	uint16_t tick = HAL_GetTick() + 1000;
	uint8_t status = 0;
	while (HAL_GetTick() < tick) {
		status = status | HAL_GPIO_ReadPin(NETSTATUS_GPIO_Port,
		NETSTATUS_GPIO_PIN);
	}

	if (status == 0) {
		HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, 0);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(PWR_CTRL_GPIO_Port, PWR_CTRL_Pin, 1);
	}
}

extern uint8_t sim5320a_signal_quality(void) {

	char reply[80];
	uint16_t replyLength = 80;

	/* AT+CMGF=1 Select SMS message format as text mode */
	stm32f410_uart_usart1_transmit("AT+CSQ\r\n");
	HAL_Delay(20);
	stm32f410_uart_get_usart1_reply(reply, replyLength);
	if (reply[2] == '+' && reply[3] == 'C' && reply[4] == 'S' && reply[5] == 'Q'
			&& reply[6] == ':') {
		if (reply[10] == 0x2C) {
			return ((uint8_t) reply[8] - 48) * 10 + ((uint8_t) reply[9] - 48);
		} else {
			return ((uint8_t) reply[8] - 48);
		}
	}
	return 99;
}

extern uint8_t sim5320a_battery_percent(void) {
	char reply[80];
	uint16_t replyLength = 80;

	/* AT+CMGF=1 Select SMS message format as text mode */
	stm32f410_uart_usart1_transmit("AT+CBC\r\n");
	HAL_Delay(400);
	stm32f410_uart_get_usart1_reply(reply, replyLength);
	if (reply[2] == '+' && reply[3] == 'C' && reply[4] == 'B' && reply[5] == 'C'
			&& reply[6] == ':') {

		if (reply[12] == 0x2C) {
			return ((uint8_t) reply[10] - 48) * 10 + ((uint8_t) reply[11] - 48);
		} else {
			return ((uint8_t) reply[10] - 48);
		}

	}
	return 0;
}

/* returns up to 5 text messages
 * returns number of messages received*/
extern uint8_t sim5320a_check_sms_messages(char messageBank[5][200]) {
	/* Wipe Message Bank for new messages */
	for (int i = 0; i < 5; i++) {
		memset(messageBank[i], 0, 200);
	}

	char reply[600];
	uint16_t replyLength = 600;

	/* Clear input buffer */
	stm32f410_uart_get_usart1_reply(reply, replyLength);

	/* Send AT+CMGL="REC UNREAD" -> Retrieve unread messages */
	stm32f410_uart_usart1_transmit("AT+CMGL=\"REC UNREAD\"\r\n");
	HAL_Delay(400);
	stm32f410_uart_get_usart1_reply(reply, replyLength);

	/* Check for OK (No messages) */
	uint8_t messageCount = 0;
	if (reply[0] == '\r' && reply[1] == '\n' && reply[2] == 'O'
			&& reply[3] == 'K') {

		return messageCount; // 0 text messages
	}

	/* Process messages */
	uint16_t index = 0;
	uint8_t messageExtraction = 0;
	uint16_t messageIndex = 0;
	/* Scan through reply and extract messages */
	while (messageCount < 5 && index < 1000) {
		/* Look for +CMGL */
		if (messageExtraction == 0) {
			if (reply[index] == '+' && reply[index + 1] == 'C'
					&& reply[index + 2] == 'M' && reply[index + 3] == 'G'
					&& reply[index + 4] == 'L') {
				messageExtraction = 1;
			}

			/* Look for the next line which the message is written on */
		} else if (messageExtraction == 1) {
			if (reply[index] == '\r' && reply[index + 1] == '\n') {
				index++;
				messageExtraction = 2;
			}

			/* Write the message to the messageBank until newline + CMGL is found */
		} else if (messageExtraction == 2) {
			messageBank[messageCount][messageIndex] = reply[index];
			messageIndex++;

			/* If \r\n+CMGL coming up soon end of this message */
			if (reply[index + 1] == '\r' && reply[index + 2] == '\n'
					&& reply[index + 3] == '+' && reply[index + 4] == 'C'
					&& reply[index + 5] == 'M' && reply[index + 6] == 'G'
					&& reply[index + 7] == 'L') {
				messageCount++;
				messageIndex = 0;
				messageExtraction = 0;

				/* If message buffer about to be exceeded */
			} else if (reply[index + 1] == '\r' && reply[index + 2] == '\n'
					&& reply[index + 3] == '\r' && reply[index + 4] == '\n'
					&& reply[index + 5] == 'O' && reply[index + 6] == 'K'
					&& reply[index + 7] == '\r' && reply[index + 8] == '\n') {

				messageCount++;
				return messageCount;
			} else if (messageIndex == 200) {
				return messageCount;
			}
		}
		index++;
	}

	/* Return number of messages */
	return messageCount;
}

