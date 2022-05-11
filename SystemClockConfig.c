#include"SystemClockConfig.h"

void SysClock_Config(void)
{
    // ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= (1UL<<16); // ENABLE HSE
	while(!(RCC->CR & (1UL<<17)));	// wait HSE ready on
	
	// Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= (1UL<<28);	// POWER ENABLE CLOCK
	PWR->CR |= (1UL<<14);	// VOLTAGE REGULATOR  *** Scale 1 mode ***
	
	// Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = 0;	//	Clear all ACR register (Access Control Register)
	FLASH->ACR |= (1UL<<10);	// Data cache RESET
	FLASH->ACR |= (1UL<<9);	//	Instruction cache ENABLE
	FLASH->ACR |= (1UL<<8);	//	Prefetch ENABLE
	FLASH->ACR |= (5UL<<0);	//  FLASH	LATENCY = 5 WS (wait states)
	
	// Configure the PRESCALARS HCLK, PCLK1, PCLK2
	RCC->CFGR &= ~(1UL<<7);	// AHB prescaler ** divided 1**
	RCC->CFGR |= (5UL<<10);	// APB1 prescaler	** divided 4 **
	RCC->CFGR |= (4UL<<13);	// APB2 prescaler ** divided 2 **
		// -> using OSC 8MHz -> SYSCLK 168MHz
		
	// Configure the MAIN PLL
	RCC->PLLCFGR = 0;		// Clear all PLLCFGR register
	RCC->PLLCFGR |= (4UL<<0);	//	MAIN PLL M (PLLM) ** 000100 or (1<<2) | divided 4 (8/4 = 2MHz) **
	RCC->PLLCFGR |= (168UL<<6);	//	MAIN PLL N (PLLN) ** 10101000 | multiply 168 (2*168 = 326MHz) **
	RCC->PLLCFGR |= (0UL<<16);	//	MAIN PLL P (PLLP) ** 00  | divided 2 (336/2 = 168MHz) **
	RCC->PLLCFGR |= (4UL<<24);	//	MAIN PLL Q (PLLQ) ** 0100  | divided 4 (84MHz) **
	RCC->PLLCFGR |= (1UL<<22);	// 	HSE oscillator clock selected as PLL and PLLI2S clock entry

	//  Enable the PLL and wait for it to become ready
	RCC->CR |= (1UL<<24);	// ENABLE the PLL
	while(!(RCC->CR & (1UL<<25)));	// wait PLL ready on
	
	// Select the Clock Source and wait for it to be set
	RCC->CFGR |= (2UL<<0);	// System clock switch ,PLL selected as system clock ** (2<<0) = 10 **
	while(!(RCC->CFGR & (2UL<<2) ));	// wait PLL used as the system clock
}

void Delay(uint32_t delay)
{
	while(delay--)
	{
		SysTick->LOAD = (168 * 1000) - 1;
		SysTick->CTRL = 5;
		SysTick->VAL = 0;
		while(!(SysTick->CTRL & (1UL<<16)));
	}
}