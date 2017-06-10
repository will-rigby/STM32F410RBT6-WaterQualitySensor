/**
 ******************************************************************************
 * @file    nucleo_adc.c
 * @author  William Rigby
 * @date    220317
 * @brief   ADC Functions
 *
 ******************************************************************************
 *     EXTERNAL FUNCTIONS
 ******************************************************************************
 * ultrasonic_rangefinder_init() - Initialise First ADC
 * read_ultrasonic_adc() - Reads the ADC connected to the ultrasonic rangefinder
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f410_ultrasonic_rangefinder.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


ADC_ChannelConfTypeDef ultrasonicChannel;

/* ADC1 init function */
extern void ultrasonic_rangefinder_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC1_CHANNEL12_GPIO_CLK_ENABLE();
	Ultrasonic_Power_Pin_CLK_ENABLE();
	ADC1_CLK_ENABLE();

	/*Configure GPIO pin : Ultrasonic_Power_Pin_Pin */
	GPIO_InitStruct.Pin = Ultrasonic_Power_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Ultrasonic_Power_Pin_GPIO_Port, &GPIO_InitStruct);

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	rangeFinderAdc.Instance = ADC1;
	rangeFinderAdc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	rangeFinderAdc.Init.Resolution = ADC_RESOLUTION_12B;
	rangeFinderAdc.Init.ScanConvMode = DISABLE;
	rangeFinderAdc.Init.ContinuousConvMode = DISABLE;
	rangeFinderAdc.Init.DiscontinuousConvMode = DISABLE;
	rangeFinderAdc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	rangeFinderAdc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	rangeFinderAdc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	rangeFinderAdc.Init.NbrOfConversion = 1;
	rangeFinderAdc.Init.DMAContinuousRequests = DISABLE;
	rangeFinderAdc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&rangeFinderAdc) != HAL_OK) {
		fault_indicator_flash(200,200);
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	ultrasonicChannel.Channel = ADC_CHANNEL_12;
	ultrasonicChannel.Rank = 1;
	ultrasonicChannel.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&rangeFinderAdc, &ultrasonicChannel) != HAL_OK) {
		fault_indicator_flash(200,200);
	}

}

extern uint16_t read_ultrasonic_adc(void) {
	/* Turn on Range Finder */
	HAL_GPIO_WritePin(Ultrasonic_Power_Pin_GPIO_Port, Ultrasonic_Power_Pin, 1);

	/* Wait 49ms for first reading */
	HAL_Delay(50);

	/* Set input channel to conductivity channel */
	HAL_ADC_ConfigChannel(&rangeFinderAdc, &ultrasonicChannel);

	/*Start ADC Conversion */
	HAL_ADC_Start(&rangeFinderAdc);

	/* Wait for ADC Conversion to Complete */
	while (HAL_ADC_PollForConversion(&rangeFinderAdc, 10) != HAL_OK)
		;

	/* Get Reading and scale to inches */
	uint32_t adcReading = (((uint32_t) HAL_ADC_GetValue(&rangeFinderAdc))*512)/4096;

	/* Turn off Range Finder */
	HAL_GPIO_WritePin(Ultrasonic_Power_Pin_GPIO_Port, Ultrasonic_Power_Pin, 0);

	return (uint16_t) adcReading;
}
