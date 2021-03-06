/* Includes ------------------------------------------------------------------*/
#include "stm32f410_rtc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private Function Definitions */
extern void stm32f410_rtc_init(void) {
	/* Disable Write Protection */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	/* Program Calender */
	RTC->ISR |= (1 << 7); // Program the INIT bit
	/*
	while (!((RTC->ISR) & (1 << 6)))
		; // Wait until INITF is set
	*/
	HAL_Delay(1);
	RTC->PRER |= 255; // Set Sync Prescaler
	RTC->PRER |= (127 << 16); // Set ASync Prescaler
	RTC->ISR &= ~(1 << 7); // Clear INIT bit

	EXTI->PR = 0x00400000; // Clear event pending bit
	EXTI->EMR |= (1<<22); // Enable EXTI Line 22 event mask
	EXTI->RTSR |= (1<<22); // Enable EXTI Line 22 Rising Edge Trigger

}

extern void stm32f410_rtc_program_wakeup(uint16_t delay) {
	/* Disable Write Protection */
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
	RTC->CR &= ~(1 << 10); // Clear WUTE
	/*
	while (!(RTC->ISR & (1 << 10)))
		; // Wait until WUTWF is set
	*/
	HAL_Delay(1);
	RTC->CR |= (1<<14); // Enable Wake-up Interrupt
	RTC->WUTR = delay; // Program Timer
	RTC->CR |= (1 << 10);
	//NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

extern void stm32f410_rtc_enter_stop(void) {
	EXTI->PR = 0x00400000;

	PWR->CR &= ~(1 << 1); // Clear PDDS
	PWR->CR |= 1;
	PWR->CR |= (1 << 10); // Low-power regulator in Low Voltage and Flash memory in Deep Sleep mode
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFE(); // Enter sleep mode
	SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

extern void stm32f410_rtc_exit_stop(void){
	RTC->CR &= ~(1<<14); // Disable Wake-up Interrupt
	RTC->ISR &= ~(1<<10); // Clear WUTF Flag
	PWR->CR |= (1<<2); // Clear the Power Wake-up Flag (WUF)
	EXTI->PR = 0x00400000; // Clear event pending bit


}
