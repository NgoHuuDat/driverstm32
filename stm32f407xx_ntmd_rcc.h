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
	

#ifndef __STM32F407xx_NTMD_RCC_H__
#define __STM32F407xx_NTMD_RCC_H__

#include "stm32f407xx.h"


/*******************************************************
	*
	* RCC PLL configuration structure definition
	*
*******************************************************/

typedef struct
{
  uint32_t PLLState;		// PLL Status ** RCC_PLL_ON or RCC_PLL_OFF **
  uint32_t PLLSource;		// PLL Source ** HSI_OSC or HSE_OSC **
  uint32_t PLLM;				// Division factor for the main PLL ** 2<= PLLM <= 63**
  uint32_t PLLN;				// Main PLL multiplication factor for VCO ** 50 <= PLLN <= 432 **
  uint32_t PLLP;				// Main PLL division factor for main system clock ** PLLP = 2( 00 ), 4( 01 ), 6( 10 ), or 8( 11 ) **
  uint32_t PLLQ;				// Main PLL division factor for USB OTG FS, SDIO and random number generator clocks ** 2 <= PLLQ <= 15 **
	
}RCC_PLLInitTDef;


/*******************************************************
	*
	* RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition
	*
*******************************************************/

typedef struct
{
  uint32_t OscillatorType;                    
  RCC_PLLInitTDef PLL;        // PLL structure ** PLL STRUCT **
	
}RCC_OscInitTDef;


/*******************************************************
	*
	* RCC System, AHB and APB busses clock configuration structure definition
	*
*******************************************************/

typedef struct
{   
  uint32_t SYSCLKSource;      // System clock switch ** SYSTEM CLOCK SORUCE **  
  uint32_t AHBCLKDivider;     // AHB prescaler ** DIVIDED x **  
  uint32_t APB1CLKDivider;    // APB1 prescaler ** DIVIDED x **   
  uint32_t APB2CLKDivider; 		// APB2 prescaler ** DIVIDED x **
	
}RCC_ClkInitTDef;


/*******************************************************
	*
	* RCC_AHB1_Clock_Enable AHB1 Peripheral Clock Enable
	*
*******************************************************/

#define __NTMD_RCC_GPIOA_CLK_ENABLE()   (RCC->AHB1ENR |= (1<<0))		// ENABLE the GPIOA CLOCK	** GPIOA CLOCK ENABLE **
#define __NTMD_RCC_GPIOB_CLK_ENABLE()   (RCC->AHB1ENR |= (1<<1))		// ENABLE the GPIOB CLOCK	** GPIOB CLOCK ENABLE **
#define __NTMD_RCC_GPIOC_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<2))		// ENABLE the GPIOC CLOCK	** GPIOC CLOCK ENABLE **
#define __NTMD_RCC_GPIOD_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<3))		// ENABLE the GPIOD CLOCK	** GPIOD CLOCK ENABLE **
#define __NTMD_RCC_GPIOE_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<4))		// ENABLE the GPIOE CLOCK	** GPIOE CLOCK ENABLE **
#define __NTMD_RCC_GPIOF_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<5))		// ENABLE the GPIOF CLOCK	** GPIOF CLOCK ENABLE **
#define __NTMD_RCC_GPIOG_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<6))		// ENABLE the GPIOG CLOCK	** GPIOG CLOCK ENABLE **
#define __NTMD_RCC_GPIOH_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<7))		// ENABLE the GPIOH CLOCK	** GPIOH CLOCK ENABLE **
#define __NTMD_RCC_GPIOI_CLK_ENABLE()  	(RCC->AHB1ENR |= (1<<8))		// ENABLE the GPIOI CLOCK	** GPIOI CLOCK ENABLE **


/*******************************************************
	*
	* RCC_AHB1_Clock_Disable AHB1 Peripheral Clock Disable
	*
*******************************************************/

#define __NTMD_RCC_GPIOA_CLK_DISABLE()		(RCC->AHB1ENR &= ~(1<<0))		// DISABLE the GPIOA CLOCK	** GPIOA CLOCK DISABLE **
#define __NTMD_RCC_GPIOB_CLK_DISABLE()		(RCC->AHB1ENR &= ~(1<<1))		// DISABLE the GPIOB CLOCK	** GPIOB CLOCK DISABLE **
#define __NTMD_RCC_GPIOC_CLK_DISABLE()   	(RCC->AHB1ENR &= ~(1<<2))		// DISABLE the GPIOC CLOCK	** GPIOC CLOCK DISABLE **
#define __NTMD_RCC_GPIOD_CLK_DISABLE()   	(RCC->AHB1ENR &= ~(1<<3))		// DISABLE the GPIOD CLOCK	** GPIOD CLOCK DISABLE **
#define __NTMD_RCC_GPIOE_CLK_DISABLE()		(RCC->AHB1ENR &= ~(1<<4))		// DISABLE the GPIOE CLOCK	** GPIOE CLOCK DISABLE **
#define __NTMD_RCC_GPIOF_CLK_DISABLE()		(RCC->AHB1ENR &= ~(1<<5))		// DISABLE the GPIOF CLOCK	** GPIOF CLOCK DISABLE **
#define __NTMD_RCC_GPIOG_CLK_DISABLE()   	(RCC->AHB1ENR &= ~(1<<6))		// DISABLE the GPIOG CLOCK	** GPIOG CLOCK DISABLE **
#define __NTMD_RCC_GPIOH_CLK_DISABLE()   	(RCC->AHB1ENR &= ~(1<<7))		// DISABLE the GPIOH CLOCK	** GPIOH CLOCK DISABLE **
#define __NTMD_RCC_GPIOI_CLK_DISABLE()   	(RCC->AHB1ENR &= ~(1<<8))		// DISABLE the GPIOI CLOCK	** GPIOI CLOCK DISABLE **

/*******************************************************
	*
	* RCC_Exported_Constants RCC Exported Constants
	*
*******************************************************/


/*******************************************************
	*
	* RCC_HSE_Config HSE/HSI Config
	*
*******************************************************/
#define RCC_HSE                      16U
#define RCC_HSI                      0U

/*******************************************************
	*
	* RCC_PLL_Config PLL Config
	*
*******************************************************/

#define RCC_PLL_OFF                       0U
#define RCC_PLL_ON                        1U


/*******************************************************
	*
	* RCC_PLLP_Clock_Divider PLLP Clock Divider
	*
*******************************************************/

#define RCC_PLLP_DIV2                  0U
#define RCC_PLLP_DIV4                  1U
#define RCC_PLLP_DIV6                  2U
#define RCC_PLLP_DIV8                  3U


/*******************************************************
	*
	* RCC_PLL_Clock_Source PLL Clock Source
	*
*******************************************************/

#define RCC_PLLSOURCE_HSI                0U
#define RCC_PLLSOURCE_HSE                1U



/*******************************************************
	*
	* RCC_System_Clock_Source System Clock Source
	*
*******************************************************/

#define RCC_SYSCLKSOURCE_HSI             0U
#define RCC_SYSCLKSOURCE_HSE             1U
#define RCC_SYSCLKSOURCE_PLLCLK          2U


/*******************************************************
	*
	* RCC_AHB_Clock_Source AHB Clock Source
	*
*******************************************************/

#define RCC_SYSCLK_DIV1                  8U
#define RCC_SYSCLK_DIV2                  7U
#define RCC_SYSCLK_DIV4                  6U
#define RCC_SYSCLK_DIV8                  5U
#define RCC_SYSCLK_DIV16                 4U
#define RCC_SYSCLK_DIV64                 3U
#define RCC_SYSCLK_DIV128                2U
#define RCC_SYSCLK_DIV256                1U
#define RCC_SYSCLK_DIV512                0U


/*******************************************************
	*
	* RCC_APB1_APB2_Clock_Source APB1/APB2 Clock Source
	*
*******************************************************/

#define RCC_HCLK_DIV1                    0U
#define RCC_HCLK_DIV2                    4U
#define RCC_HCLK_DIV4                    5U
#define RCC_HCLK_DIV8                    6U
#define RCC_HCLK_DIV16                   7U






/*******************************************************
	*
	* RCC_Exported_Functions
	*
*****************************************************/


/*******************************************************
	*
	* Initialization and de-initialization functions
	*
*****************************************************/
void NTMD_RCC_OscConfig(RCC_OscInitTDef *RCC_OscInitStruct);
void NTMD_RCC_ClockConfig(RCC_ClkInitTDef *RCC_ClkInitStruct, uint32_t FLatency);

void NTMD_Delay(uint32_t delay);


#endif	/* __STM32F4xx_NTMD_RCC_H__ */
