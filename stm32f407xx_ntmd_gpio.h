/******************************************************
*
*			NGOHUUDAT
*			COMPUTER ENGINEERING TECHNOLOGY
*			ngohuudat2001@gmail.com
*
*
*			GPIO Configration Functions
*			Version: 0.1
*
*
*			V0.1 - 31.03.2022
*
******************************************************/


#ifndef __STM32F407xx_NTMD_GPIO_H__
#define __STM32F407xx_NTMD_GPIO_H__


#include "stm32f407xx.h"                 


/*******************************************************
	*
	* GPIO Init structure definition
	*
*****************************************************/

typedef struct
{
  uint32_t Pin;       
  uint32_t Mode;      
  uint32_t Pull;     
  uint32_t Speed;     
  uint32_t Alternate; 
	
}GPIO_InitTDef;


/*******************************************************
	*
	* GPIO Bit SET and Bit RESET enumeration 
	*
*****************************************************/

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;


/*******************************************************
	*
	* GPIO_pins_define GPIO pins define
	*
*****************************************************/

#define GPIO_PIN_0                 ((uint16_t)0x0001)  // Pin 0 selected	** GPIOA CLOCK ENABLE **
#define GPIO_PIN_1                 ((uint16_t)0x0002)  // Pin 1 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_2                 ((uint16_t)0x0004)  // Pin 2 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_3                 ((uint16_t)0x0008)  // Pin 3 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_4                 ((uint16_t)0x0010)  // Pin 4 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_5                 ((uint16_t)0x0020)  // Pin 5 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_6                 ((uint16_t)0x0040)  // Pin 6 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_7                 ((uint16_t)0x0080)  // Pin 7 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_8                 ((uint16_t)0x0100)  // Pin 8 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_9                 ((uint16_t)0x0200)  // Pin 9 selected  ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_10                ((uint16_t)0x0400)  // Pin 10 selected 	** GPIOA CLOCK ENABLE **
#define GPIO_PIN_11                ((uint16_t)0x0800)  // Pin 11 selected   ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_12                ((uint16_t)0x1000)  // Pin 12 selected   ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_13                ((uint16_t)0x2000)  // Pin 13 selected   ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_14                ((uint16_t)0x4000)  // Pin 14 selected   ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_15                ((uint16_t)0x8000)  // Pin 15 selected   ** GPIOA CLOCK ENABLE **
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  // All pins selected 	** GPIOA CLOCK ENABLE **


/*******************************************************
	*
	* GPIO_mode_define GPIO mode define
	*	GPIO Configuration Mode
	*		Elements values convention: 0x00WX00YZ
	*			- W  : EXTI trigger detection on 3 bits
	*			- X  : EXTI mode (IT or Event) on 2 bits
	*			- Y  : Output type (Push Pull or Open Drain) on 1 bit
	*			- Z  : GPIO mode (Input, Output, Alternate or Analog) on 2 bits
	*
*****************************************************/

#define  GPIO_MODE_INPUT                        MODE_INPUT                                                  // Input Floating Mode           
#define  GPIO_MODE_OUTPUT_PP                    (MODE_OUTPUT | OUTPUT_PP)                                   // Output Push Pull Mode                 
#define  GPIO_MODE_OUTPUT_OD                    (MODE_OUTPUT | OUTPUT_OD)                                   // Output Open Drain Mode                
#define  GPIO_MODE_AF_PP                        (MODE_AF | OUTPUT_PP)                                       // Alternate Function Push Pull Mode 
#define  GPIO_MODE_AF_OD                        (MODE_AF | OUTPUT_OD)                                       // Alternate Function Open Drain Mode

#define  GPIO_MODE_ANALOG                       MODE_ANALOG                                                 // Analog Mode 
    
#define  GPIO_MODE_IT_RISING                    (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                     // External Interrupt Mode with Rising edge trigger detection
#define  GPIO_MODE_IT_FALLING                   (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                    // External Interrupt Mode with Falling edge trigger detection
#define  GPIO_MODE_IT_RISING_FALLING            (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)   // External Interrupt Mode with Rising/Falling edge trigger detection
 
#define  GPIO_MODE_EVT_RISING                   (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                     // External Event Mode with Rising edge trigger detection 
#define  GPIO_MODE_EVT_FALLING                  (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                    // External Event Mode with Falling edge trigger detection
#define  GPIO_MODE_EVT_RISING_FALLING           (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)   // External Event Mode with Rising/Falling edge trigger detection



/*******************************************************
	*
	* GPIO_speed_define  GPIO speed define
	*
	*	GPIO Output Maximum frequency
	*
*****************************************************/

#define  GPIO_SPEED_LOW         0x0U	 // Speed Low ** 2 MHz **
#define  GPIO_SPEED_MEDIUM      0x1U  // Speed Medium ** 12,5 MHz to 50 MHz **
#define  GPIO_SPEED_HIGH        0x2U  // Speed High ** 12,5 MHz to 50 MHz **
#define  GPIO_SPEED_VERY_HIGH   0x3U  // Speed Very High ** 50 MHz to 200 MHz **/

 
/*******************************************************
	*
	* GPIO_pull_define GPIO pull define
	*
	*	GPIO Pull-Up or Pull-Down Activation
	*
*****************************************************/

#define  GPIO_NOPULL        0x0U   // No Pull-up or Pull-down activation
#define  GPIO_PULLUP        0x1U   // Pull-up activation                 
#define  GPIO_PULLDOWN      0x2U   // Pull-down activation               



/*******************************************************
	*
	* GPIO_Exported_Functions
	*
*****************************************************/

/*******************************************************
	*
	* Initialization and de-initialization functions
	*
*****************************************************/

void  NTMD_GPIO_Init(GPIO_TypeDef*  GPIOx, GPIO_InitTDef* GPIO_Init);
void  NTMD_GPIO_DeInit(GPIO_TypeDef*  GPIOx, uint32_t GPIO_Pin);



/*******************************************************
	*
	* IO operation functions
	*
*****************************************************/

GPIO_PinState NTMD_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void NTMD_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void NTMD_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void NTMD_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void NTMD_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


/*******************************************************
	*
	* GPIO_Private_Constants GPIO Private Constants
	*
*****************************************************/

#define GPIO_MODE_POS                           0U
#define GPIO_MODE                               (0x3UL << GPIO_MODE_POS)
#define MODE_INPUT                              (0x0UL << GPIO_MODE_POS)
#define MODE_OUTPUT                             (0x1UL << GPIO_MODE_POS)
#define MODE_AF                                 (0x2UL << GPIO_MODE_POS)
#define MODE_ANALOG                             (0x3UL << GPIO_MODE_POS)

#define OUTPUT_TYPE_POS                         4U
#define OUTPUT_TYPE                             (0x1UL << OUTPUT_TYPE_POS)
#define OUTPUT_PP                               (0x0UL << OUTPUT_TYPE_POS)
#define OUTPUT_OD                               (0x1UL << OUTPUT_TYPE_POS)

#define EXTI_MODE_POS	                          16U
#define EXTI_MODE                               (0x3UL << EXTI_MODE_POS)
#define EXTI_IT                                 (0x1UL << EXTI_MODE_POS)
#define EXTI_EVT                                (0x2UL << EXTI_MODE_POS)

#define TRIGGER_MODE_POS                         20U
#define TRIGGER_MODE                            (0x7UL << TRIGGER_MODE_POS)
#define TRIGGER_RISING                          (0x1UL << TRIGGER_MODE_POS)
#define TRIGGER_FALLING                         (0x2UL << TRIGGER_MODE_POS)



#endif /* __STM32F407xx_NTMD_GPIO_H__ */
