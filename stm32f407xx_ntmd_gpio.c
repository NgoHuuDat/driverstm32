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


#include "stm32f407xx_ntmd_gpio.h"

#define GPIO_NUMBER   16U


/*******************************************************
	*
	* GPIO_Exported_Functions GPIO Exported Functions
	*
	*	Initialization and Configuration functions
	*
*****************************************************/
/*
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
*/

/*******************************************************
	*
	* Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init
	*
	*	GPIO_Init pointer to a GPIO_InitType structure that contains
	*
*****************************************************/
void NTMD_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTDef *GPIO_Init)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;

  for(position = 0U; position < GPIO_NUMBER; position++)
  {
		
    ioposition = 0x01U << position;		//	Get the GPIO position
    iocurrent = (GPIO_Init->Pin) & ioposition;	//	Get the current GPIO position

    if(iocurrent == ioposition)
    {
      //	GPIO Mode Configuration
			
      // In case of Output or Alternate function mode selection 
      if(((GPIO_Init->Mode & GPIO_MODE) == MODE_OUTPUT) || (GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
      {
        GPIOx->OSPEEDR |= (GPIO_Init->Speed << (position * 2U));	// Configure the GPIO Speed
        GPIOx->OTYPER |= ((GPIO_Init->Mode & OUTPUT_TYPE) << position);	// Configure the GPIO Output Type
       }

      if((GPIO_Init->Mode & GPIO_MODE) != MODE_ANALOG)
      {        
        GPIOx->PUPDR |= ((GPIO_Init->Pull) << (position * 2U));	// Activate the Pull-up or Pull down the GPIO 	** PULL-UP or PULL-DOWN **
      }

      // In case of Alternate function mode selection 
      if((GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
      {
        // Configure Alternate function mapped with the current GPIO
        GPIOx->AFR[position >> 3U] |= ((uint32_t)(GPIO_Init->Alternate) << (((uint32_t)position & 0x07U) * 4U));
      }

      // Configure GPIO Direction mode	** INPUT, OUTPUT, ALTERNATE or ANALOG **
      GPIOx->MODER |= ((GPIO_Init->Mode & GPIO_MODE) << (position * 2U));	//	MODER ** INPUT(00), OUTPUT(01), AFMODE(10), ANALOG(11) **

    }
  }
}


/*******************************************************
	*
	* De-initializes the GPIOx peripheral registers to their default reset values
	*
	*	GPIO_Pin specifies the port bit to be written
	*
*****************************************************/
void NTMD_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;

  /* Configure the port pins */
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
   
    ioposition = 0x01U << position;		// Get the GPIO position
    iocurrent = (GPIO_Pin) & ioposition;		// Get the current GPIO position

    if(iocurrent == ioposition)
    {
      // GPIO Mode Configuration
      // Configure GPIO Direction in Input Floating Mode
      GPIOx->MODER &= (uint32_t)~(3 << (position * 2U));	//MODER ** INPUT **

      // Configure the default Alternate Function in current GPIO 
      GPIOx->AFR[position >> 3U] &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U));	//AFR ** AF0	**

      // Deactivate the Pull-up and Pull-down resistor for the current GPIO 
      GPIOx->PUPDR &= (uint32_t)~(3 << (position * 2U));	// PULL	** NO PULL-UP PULL DOWN **

      // Configure the default value GPIO Output Type 
      GPIOx->OTYPER  &= ~(1 << position);		// OUTPUR ** PUSH-PULL **

      // Configure the default value for GPIO Speed 
      GPIOx->OSPEEDR &= (uint32_t)~(3 << (position * 2U));	//SPEED ** LOW SPEED **
    }
  }
}


/*******************************************************
	*
	* GPIO Read and Write
	*
*****************************************************/
/*
 ===============================================================================
                       ##### GPIO operation functions #####
 ===============================================================================
*/
/*******************************************************
	*
	* Reads the specified input port pin
	*
*****************************************************/
GPIO_PinState NTMD_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;
	bitstatus = GPIO_PIN_RESET;

  if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  
  if((GPIOx->IDR & GPIO_Pin) == (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_RESET;
  }
  
  return bitstatus;
}


/*******************************************************
	*
	* Sets or clears the selected data port bit
	*
*****************************************************/
void NTMD_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  if(PinState == GPIO_PIN_SET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  
  if(PinState == GPIO_PIN_RESET)
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
  }
}


/*******************************************************
	*
	* Toggles the specified GPIO pins.
	*
*****************************************************/
void NTMD_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr;

  odr = GPIOx->ODR;
  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}


/*******************************************************
	*
	* GPIO_Pin Specifies the pins connected EXTI line
	*
*****************************************************/

void NTMD_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  // EXTI line interrupt detected
  if((EXTI->PR &(GPIO_Pin)) != 0U)
  {
    EXTI->PR = GPIO_Pin;
    NTMD_GPIO_EXTI_Callback(GPIO_Pin);
  }
}


/*******************************************************
	*
	* EXTI line detection callbacks
	*
***********************************************/

void NTMD_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // Prevent unused argument(s) compilation warning 
	(void)GPIO_Pin;
}

