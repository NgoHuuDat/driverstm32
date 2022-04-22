/******************************************************
*
*			NGOHUUDAT
*			COMPUTER ENGINEERING TECHNOLOGY
*			ngohuudat2001@gmail.com
*
*
*			System Configration Functions
*			Version: 0.1
*
*
*			V0.1 - 31.03.2022
*
******************************************************/


#include "stm32f407xx_ntmd_rcc.h"


void NTMD_RCC_OscConfig(RCC_OscInitTDef *RCC_OscInitStruct)
{	
	/*------------------------------- HSE Configuration ------------------------*/
	
	// ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= (1 <<RCC_OscInitStruct->OscillatorType); // ENABLE HSE or HSI
	while(!(RCC->CR & (1 <<(RCC_OscInitStruct->OscillatorType + 1))));	// wait HSE or HSI ready on
	
	// Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= (1 <<28);	// POWER ENABLE CLOCK
	PWR->CR |= (1 <<14);	// VOLTAGE REGULATOR  *** Scale 1 mode ***
	
  // Configure the MAIN PLL
	RCC->PLLCFGR = 0x00000000;		// Clear all PLLCFGR register
	RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLM <<0);	//	MAIN PLL M (PLLM) ** divided 2 -> 63 **
	RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLN <<6);	//	MAIN PLL N (PLLN) ** multiply 50 -> 432 **
	RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLP <<16);	//	MAIN PLL P (PLLP) ** divided 2(00) | 4(01) | 6(10) | 8(11) **
	RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLQ <<24);	//	MAIN PLL Q (PLLQ) ** divided 2 -> 15 **
	RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLSource <<22);	// 	HSE oscillator or HSI clock selected as PLL and PLLI2S clock entry
	
	// Enable the PLL and wait for it to become ready
	RCC->CR |= (RCC_OscInitStruct->PLL.PLLState <<24);	// ENABLE the PLL
	while(!(RCC->CR & (RCC_OscInitStruct->PLL.PLLState <<25)));	// wait PLL ready on
}


void NTMD_RCC_ClockConfig(RCC_ClkInitTDef *RCC_ClkInitStruct, uint32_t FLatency)
{
	//	Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = 0;	//	Clear all ACR register (Access Control Register)
	FLASH->ACR |= (1 <<10);	// Data cache RESET
	FLASH->ACR |= (1 <<9);	//	Instruction cache ENABLE
	FLASH->ACR |= (1 <<8);	//	Prefetch ENABLE
	FLASH->ACR |= (FLatency <<0);	//  FLASH	LATENCY = x WS (wait states) ** 0 -> 7 wait state **
	
	//	Configure the PRESCALARS HCLK, PCLK1, PCLK2
	RCC->CFGR &= ~(RCC_ClkInitStruct->AHBCLKDivider <<4);	// AHB prescaler ** divided x**
	RCC->CFGR |= (RCC_ClkInitStruct->APB1CLKDivider <<10);	// APB1 prescaler	** divided x **
	RCC->CFGR |= (RCC_ClkInitStruct->APB2CLKDivider <<13);	// APB2 prescaler ** divided x **
		
	//	Select the Clock Source and wait for it to be set
	RCC->CFGR |= (RCC_ClkInitStruct->SYSCLKSource <<0);	// System clock switch
	while(!(RCC->CFGR & (RCC_ClkInitStruct->SYSCLKSource <<2) ));	// wait used as the system clock
}

void NTMD_Delay(uint32_t delay)
{
	while(delay--)
	{
		SysTick->LOAD = (168 * 1000) - 1;
		SysTick->CTRL = 5;
		SysTick->VAL = 0;
		while(!(SysTick->CTRL & (1<<16)));
	}
	
}
