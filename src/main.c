/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
/* STM32F4 HAL Libraries */
#include "stm32f4xx.h"

/* C Libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* Application Specific Libraries */
#include "stm32f410_fault_indicator.h"
#include "stm32f410_1wire.h"
#include "stm32f410_ultrasonic_rangefinder.h"
#include "stm32f410_uart.h"
#include "stm32f410_sim5320a.h"
#include "stm32f410_i2c.h"
#include "stm32f410_atlas_scientific.h"
#include "stm32f410_rtc.h"

/* Private variables ---------------------------------------------------------*/
/* Global Board Settings */
char serverIPAddress[21]; //"125.168.189.226";"128.173.221.22"
char serverPort[6]; //"4523" "2727"
char accessPoint[21]; // telstra.wap "NXTGENPHONE
char mobileNumber[13]; // = "+61423037656"; "+17577752179"
char boardName[21]; //"UQ Board 1" "RIGBI"
uint16_t delayTime = 60; // Interval in seconds between messages
uint8_t tcpEnabled = 1; // Enables sending data over TCP
uint8_t dataCollectionMode = 0; // Specifies Collection Mode 0 = 1 sample per interval
uint8_t sendDataOverSMS = 0; // Send the data over SMS as well
uint16_t dataCollectionNumber = 0; // Keeps track of the sample number

/* Real Time Clock Variables */
RTC_HandleTypeDef hrtc;
//static __IO

/* Private function prototypes -----------------------------------------------*/
/* Hardware Functions */
void SystemClock_Config(void);
void Hardware_Init(void);
void MX_RTC_Init(void);

/* Process Incoming Messages from SMS or TCP Function*/
uint8_t process_message_bank_ip(char message[200]);
uint8_t process_message_bank_port(char message[200]);
uint8_t process_message_bank_name(char message[200]);
uint8_t process_message_bank_number(char message[200]);
uint8_t process_message_bank_apn(char message[200]);
uint8_t process_message_bank_interval(char message[200]);
void process_message_bank(char messageBank[5][200], uint8_t numberOfMessages);
void process_tcp_commands(char messageBank[200]);

/* Data Collection Functions */
void data_collect_measurement_per_interval(void);
void data_capture_and_transmission(void);
uint8_t connect_to_tcp(void);
uint8_t udp_packet(char* data);
uint8_t close_connection(void);
uint16_t low_mem_string_length(char* str);
void getDecStr(char* str, uint8_t len, uint16_t val);

/* Main Function */
int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Enable Interrupts */

	/* Initialize all configured peripherals */
	Hardware_Init();


	/* Set Default Values */
	sprintf(boardName, "UQ Board 1");
	sprintf(serverIPAddress, "125.168.189.226");
	sprintf(serverPort, "4523");
	sprintf(accessPoint, "telstra.wap");

	/* Data Collection Loop */
	while (1) {

		data_capture_and_transmission();
	}

}

/** System Clock Configuration
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 128;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	RCC_OscInitStruct.PLL.PLLR = 2;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_RTC_Init(void) {

	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	/**Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	HAL_RTC_Init(&hrtc);

	/**Initialize RTC and set the Time and Date
	 */
	if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != 0x32F2) {
		sTime.Hours = 0x0;
		sTime.Minutes = 0x0;
		sTime.Seconds = 0x0;
		sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sTime.StoreOperation = RTC_STOREOPERATION_RESET;
		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

		sDate.WeekDay = RTC_WEEKDAY_MONDAY;
		sDate.Month = RTC_MONTH_JANUARY;
		sDate.Date = 0x1;
		sDate.Year = 0x0;

		HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, 0x32F2);
	}
	/**Enable the WakeUp
	 *
	 */
	HAL_RTCEx_SetWakeUpTimer(&hrtc, 300, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 300, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);

}

void Hardware_Init(void) {
	HAL_Delay(50);
	__HAL_RCC_GPIOH_CLK_ENABLE()
	;

	fault_indicator_init();
	ultrasonic_rangefinder_init();
	//MX_RTC_Init();
	stmf410_uart_usart1_init();
	stmf410_uart_usart2_init();
	stm32f410_uart_usart1_transmit("BEFORERTC");
	oneWire_init();
	sim5320a_init();
	stm32f410_i2c_bitbang_init();
	stm32f410_rtc_init();
	stm32f410_uart_usart1_transmit("AFTERRTC");

}

uint8_t process_message_bank_ip(char message[200]) {
	/* Check for SETIP="123.123.123.123" */
	char ip[21];
	for (uint8_t i = 0; i < 21; i++) {
		ip[i] = 0;
	}
	for (uint8_t n = 0; n < 192; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'I')
				&& (message[n + 4] == 'P')) {
			uint8_t x = n + 7;
			uint8_t y = 0;

			/* Extract IP Address */
			while (message[x] != 34 && y < 15) {
				ip[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */
			for (uint8_t i = 0; i < 21; i++) {
				serverIPAddress[i] = ip[i];
			}
		}
	}
	return 0;
}

uint8_t process_message_bank_port(char message[200]) {
	/* Extract Port from SETPORT="1234" */
	char port[6];
	for (uint8_t i = 0; i < 6; i++) {
		port[i] = 0;
	}
	for (uint8_t n = 0; n < 190; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'P')
				&& (message[n + 4] == 'O') && (message[n + 5] == 'R')
				&& (message[n + 6] == 'T')) {
			uint8_t x = n + 9;
			uint8_t y = 0;

			/* Extract PORT Address */
			while (message[x] != 34 && y < 6) {
				port[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */
			for (uint8_t i = 0; i < 6; i++) {
				serverPort[i] = port[i];
			}
			return 1;
		}
	}
	return 0;
}

uint8_t process_message_bank_name(char message[200]) {
	char name[21];
	for (uint8_t i = 0; i < 21; i++) {
		name[i] = 0;
	}
	for (uint8_t n = 0; n < 190; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'N')
				&& (message[n + 4] == 'A') && (message[n + 5] == 'M')
				&& (message[n + 6] == 'E')) {
			uint8_t x = n + 9;
			uint8_t y = 0;

			/* Extract PORT Address */
			while (message[x] != 34 && y < 20) {
				name[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */

			for (uint8_t i = 0; i < 21; i++) {
				boardName[i] = name[i];
			}
			return 1;
		}
	}
	return 0;
}

uint8_t process_message_bank_number(char message[200]) {
	char mNumber[13];
	for (uint8_t i = 0; i < 13; i++) {
		mNumber[i] = 0;
	}
	for (uint8_t n = 0; n < 188; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'M')
				&& (message[n + 4] == 'O') && (message[n + 5] == 'B')
				&& (message[n + 6] == 'I') && (message[n + 7] == 'L')
				&& (message[n + 8] == 'E')) {
			uint8_t x = n + 11;
			uint8_t y = 0;

			/* Extract PORT Address */
			while (message[x] != 34 && y < 12) {
				mNumber[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */

			for (uint8_t i = 0; i < 13; i++) {
				mobileNumber[i] = mNumber[i];
			}
			return 1;
		}
	}
	return 0;
}

uint8_t process_message_bank_apn(char message[200]) {
	char apn[21];
	memset(apn, 0, 21);
	for (uint8_t n = 0; n < 181; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'A')
				&& (message[n + 4] == 'P') && (message[n + 5] == 'N')
				&& (message[n + 6] == '=') && (message[n + 7] == 34)) {
			uint8_t x = n + 8;
			uint8_t y = 0;

			/* Extract APN  */
			while (message[x] != 34 && y < 20) {
				apn[y] = message[x];
				x++;
				y++;
			}

			/* Set APN and break from this statement */
			memcpy(accessPoint, apn, 21);
			return 1;
		}
	}
	return 0;
}

uint8_t process_message_bank_interval(char message[200]) {
	char delay[5];
	for (uint8_t i = 0; i < 5; i++) {
		delay[i] = 0;
	}
	for (uint8_t n = 0; n < 189; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'D')
				&& (message[n + 4] == 'E') && (message[n + 5] == 'L')
				&& (message[n + 6] == 'A') && (message[n + 7] == 'Y')) {
			uint8_t x = n + 10;
			uint8_t y = 0;

			/* Extract PORT Address */
			while (message[x] != 34 && y < 5) {
				delay[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */
			uint16_t dTime = 0;
			for (int z = 0; z < low_mem_string_length(delay); z++) {
				dTime = dTime * 10 + (delay[z] - 48);
			}
			delayTime = dTime;
			return 1;
		}
	}
	return 0;
}

uint8_t process_message_bank_enable_tcp(char message[200]) {
	char delay[5];
	memset(delay, 0, 5);
	for (uint8_t n = 0; n < 189; n++) {
		if ((message[n] == 'S') && (message[n + 1] == 'E')
				&& (message[n + 2] == 'T') && (message[n + 3] == 'D')
				&& (message[n + 4] == 'E') && (message[n + 5] == 'L')
				&& (message[n + 6] == 'A') && (message[n + 7] == 'Y')) {
			uint8_t x = n + 10;
			uint8_t y = 0;

			/* Extract PORT Address */
			while (message[x] != 34 && y < 5) {
				delay[y] = message[x];
				x++;
				y++;
			}

			/* Set IP and break from this statement */
			uint16_t dTime = 0;
			for (int z = 0; z < low_mem_string_length(delay); z++) {
				dTime = dTime * 10 + (delay[z] - 48);
			}
			if (dTime > 30) {
				delayTime = dTime;
			} else {
				delayTime = 30;
			}
			return 1;
		}
	}
	return 0;
}

void process_message_bank(char messageBank[5][200], uint8_t numberOfMessages) {
	for (int i = 0; i < numberOfMessages; i++) {
		process_message_bank_ip(messageBank[i]);
		process_message_bank_port(messageBank[i]);
		process_message_bank_name(messageBank[i]);
		process_message_bank_number(messageBank[i]);
		process_message_bank_apn(messageBank[i]);
		process_message_bank_interval(messageBank[i]);

	}
	if (numberOfMessages > 0) {

		sim5320a_send_text_message(mobileNumber, "Settings Updated");
	}
}

void process_tcp_commands(char messageBank[200]) {
	uint8_t commandUpdated = 0;
	commandUpdated = commandUpdated | process_message_bank_ip(messageBank);
	commandUpdated = commandUpdated | process_message_bank_port(messageBank);
	commandUpdated = commandUpdated | process_message_bank_name(messageBank);
	commandUpdated = commandUpdated | process_message_bank_number(messageBank);
	commandUpdated = commandUpdated | process_message_bank_apn(messageBank);
	commandUpdated = commandUpdated
			| process_message_bank_interval(messageBank);
	if (commandUpdated) {

		sim5320a_tcp_send_data("Updated Settings");
	}
}

void data_collect_measurement_per_interval(void) {

	/* Restart all Peripherals */
	uint32_t startTime = HAL_GetTick();

	Hardware_Init();

	/* Turn on the SIM5320a  */
	sim5320a_power_on();

	/* Turn on the SIM5320a  */
	if (sim5320a_activate() == 0) {

		sim5320a_activate_sms();
		char messageBank[5][200];
		uint8_t numberOfMessages = sim5320a_check_sms_messages(messageBank);
		process_message_bank(messageBank, numberOfMessages);
		sim5320a_set_default_parameters(accessPoint, serverPort,
				serverIPAddress);

		/* Get data */
		char pH[20]; //read_ph_adc();
		stm32f410_as_read_pH(pH, 10);

		char conductivity[20]; //read_conductivity_adc();
		stm32f410_as_read_conductivity(conductivity, 10);
		uint8_t ph0 = 1;
		uint8_t cond0 = 1;
		for (int i = 0; i < 10; i++) {
			if (pH[i] != 0) {
				ph0 = 0;
			}
			if (conductivity[0] != 0) {
				cond0 = 0;
			}
		}
		if (cond0) {
			conductivity[0] = '0';
		}
		if (ph0) {
			pH[0] = '0';
		}

		uint16_t ultrasonic = read_ultrasonic_adc();
		char ultrasonicString[6];
		getDecStr(ultrasonicString, 6, ultrasonic);

		int16_t temperature[2];
		char temperatureString[2][10];
		onewire_read_ds18b20_temp_int16(temperature);
		getDecStr(temperatureString[0], 10, temperature[0]);
		getDecStr(temperatureString[1], 10, temperature[1]);

		uint8_t signalQuality = sim5320a_signal_quality();
		char sigQual[5];
		getDecStr(sigQual, 5, signalQuality);

		uint8_t batteryStatus = sim5320a_battery_percent();
		char batStat[5];
		getDecStr(batStat, 5, batteryStatus);

		/* Message = BOARDNAME, DATACOLLECTIONNUMBER, TEMP1.TEMP2, conductivity, pH, range, bat, sig		 */
		/*                    12                    34    56            78  91     12   34   56 */
		/* Format and send data over TCP*/
		/* Create Message */
		char dataCollectionNumberString[6];
		getDecStr(dataCollectionNumberString, 6, dataCollectionNumber);

		uint16_t dataLength = 16; // ,' ' and \r\n and . in temp
		dataLength += low_mem_string_length(boardName);
		dataLength += low_mem_string_length(dataCollectionNumberString);
		dataLength += low_mem_string_length(temperatureString[0]);
		dataLength += low_mem_string_length(temperatureString[1]);
		dataLength += low_mem_string_length(conductivity);
		dataLength += low_mem_string_length(pH);
		dataLength += low_mem_string_length(ultrasonicString);
		dataLength += low_mem_string_length(sigQual);
		dataLength += low_mem_string_length(batStat);

		if (connect_to_tcp() == 0) {

			/* Send Actual Message */
			char messageLength[5]; // length of data
			getDecStr(messageLength, 5, dataLength);

			stm32f410_uart_usart1_transmit("AT+CIPSEND=0,");
			stm32f410_uart_usart1_transmit(messageLength);
			stm32f410_uart_usart1_transmit("\r\n");
			HAL_Delay(100);
			stm32f410_uart_usart1_transmit(serverIPAddress);
			stm32f410_uart_usart1_transmit("\",");
			stm32f410_uart_usart1_transmit(serverPort);
			stm32f410_uart_usart1_transmit("\r\n");
			HAL_Delay(100);

			stm32f410_uart_usart1_transmit(boardName);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(dataCollectionNumberString);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(temperatureString[0]);
			stm32f410_uart_usart1_transmit(".");
			stm32f410_uart_usart1_transmit(temperatureString[1]);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(conductivity);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(pH);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(ultrasonicString);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(sigQual);
			stm32f410_uart_usart1_transmit(", ");

			stm32f410_uart_usart1_transmit(batStat);
			stm32f410_uart_usart1_transmit("\r\n");

			HAL_Delay(500);

			char messageFromTCPServer[80];
			HAL_Delay(10000); // Wait seconds for a reply

			/* Get any messages from TCP Server if there are any */
			stm32f410_uart_get_usart1_reply(messageFromTCPServer, 80);
			process_tcp_commands(messageFromTCPServer);

			/* Close the TCP Server connection */
			close_connection();

		}
		dataCollectionNumber++;
	} else {
		/* Error */
		stm32f410_uart_usart1_transmit("Connect Failed.");
		for (int i = 0; i < 10; i++) {
			fault_indicator_on();
			HAL_Delay(200);
			fault_indicator_off();
			HAL_Delay(200);
			fault_indicator_on();
			HAL_Delay(200);
			fault_indicator_off();
			HAL_Delay(800);
		}
	}
	sim5320a_power_off();

	/* Disable all peripherals and sleep */
	HAL_ADC_DeInit(&rangeFinderAdc);
	stm32f410_as_pH_sleep();
	stm32f410_as_conductivity_sleep();

	/* Calculate Delay (if reading takes 30 seconds, and interval is 60 seconds, sleep for 30 seconds) */
	uint32_t calculatedDelayInterval = delayTime
			- (HAL_GetTick() - startTime) / 1000;

	/* Ensure Delay Does not Exceed 60 minutes */
	if (calculatedDelayInterval > 3600) {
		calculatedDelayInterval = 60;
	}

	char sleepTime[10];
	getDecStr(sleepTime, 10, calculatedDelayInterval);
	stm32f410_uart_usart1_transmit(sleepTime);

	/* Enter Sleep */
	stm32f410_rtc_program_wakeup((uint16_t) calculatedDelayInterval);
	stm32f410_rtc_enter_stop();

	/* On Wake Up */
	HAL_Init();
	SystemClock_Config();

	/*for (uint32_t i; i < calculatedDelayInterval; i++) {
	 HAL_Delay(1000);
	 }*/
}

void data_capture_and_transmission(void) {

	if (1) {
		data_collect_measurement_per_interval();
	}
}

uint8_t connect_to_tcp(void) {
	char reply[80];
	uint16_t replyLength = 80;

	/* Define socket PDP context */
	stm32f410_uart_get_usart1_reply(reply, replyLength); // Clear Input Buffer

	stm32f410_uart_usart1_transmit("AT+CGSOCKCONT=1,\"IP\",\"");
	stm32f410_uart_usart1_transmit(accessPoint);
	stm32f410_uart_usart1_transmit("\"\r\n");
	HAL_Delay(100);

	/* Get Reply from PDP command */
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
	stm32f410_uart_usart1_transmit("AT+CIPOPEN=0,\"TCP\",\"");
	stm32f410_uart_usart1_transmit(serverIPAddress);
	stm32f410_uart_usart1_transmit("\",");
	stm32f410_uart_usart1_transmit(serverPort);
	stm32f410_uart_usart1_transmit("\r\n");
	HAL_Delay(1000);
	return 0;
}

uint8_t udp_packet(char* data) {
	char message[200]; // buffer to store message
	uint8_t messageLength = low_mem_string_length(data); // length of data

	sprintf(message, "AT+CIPSEND=0,%d,\"125.168.189.226\",4523\r\n",
			messageLength);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(100);

	sprintf(message, "%s", data);
	stm32f410_uart_usart1_transmit(message);
	HAL_Delay(500);

	return 0;
}

uint8_t close_connection(void) {
	stm32f410_uart_usart1_transmit("AT+CIPCLOSE=0\r\n");
	HAL_Delay(600);

	stm32f410_uart_usart1_transmit("AT+NETCLOSE\r\n");
	HAL_Delay(100);

	/* Set internal flag to closed */

	return 0;
}

uint16_t low_mem_string_length(char* str) {
	uint16_t length = 0;
	while (str[length] != 0) {
		length++;
	}
	return length;
}

void getDecStr(char* str, uint8_t len, uint16_t val) {
	/*
	 uint8_t i;

	 for (i = 1; i <= len; i++) {
	 str[len - i] = (char) ((val % 10UL) + '0');
	 val /= 10;
	 }

	 str[i - 1] = '\0';
	 */
	if (val == 0) {
		str[0] = '0';
		for (uint8_t i = 1; i < len; i++) {
			str[i] = '\0';
		}
	} else {
		char remainders[20];
		/* Set Remainders array to null */
		int16_t x;
		int16_t i;
		for (x = 0; x < len; x++) {
			str[x] = '\0';
		}
		for (x = 0; x < 20; x++) {
			remainders[x] = '\0';
		}
		/* extract place values */
		for (i = 1; i <= len; i++) {
			remainders[i] = (char) ((val % 10) + '0');
			val /= 10;
		}
		i = 0;
		int16_t found = 0;
		int16_t y = 0;
		/* While null characters skip*/
		for (i = (len - 1); i >= 0; i--) {
			if ((found == 0) && (remainders[i] != '0')) {
				found = 1;
				str[y] = remainders[i];
				y++;
			} else if (found == 1) {
				str[y] = remainders[i];
				y++;
			}
			if (y == len) {
				return;
			}
		}

	}

}
