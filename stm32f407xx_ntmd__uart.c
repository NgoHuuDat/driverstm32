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

#include "stm32f407xx_ntmd__uart.h"

/*
	
	STM32F4 USART Library with register based
	
	This document is tested with CP2102 USB to TTL Converter
	
	Connection
	---------------------------
	
	Board TX 	-----> CP2102 RX
	Board RX  	-----> CP2102 TX
	Board GND 	-----> CP2102 GND
	
	For USART1 Communication:
		- Used pins are PB6 and PB7
		- PA9 and PA10 not used for CP2102 communication on Discovery Board.
			Because, these pins also used on USB communication with connected
			Capacitor. This is the reason why used PB6 and PB7 for USART1.
			
	Features
	---------------------------
	- Other USARTs functions will add
	
*/


void USART1_Init(uint32_t BAUDRATE)
{

	/* GPIO port B Clock Enable  */
	RCC->AHB1ENR  |= 0x00000002;

	/*
	GPIOx_AFR[0] = GPIOx_AFRL
	GPIOx_AFR[1] = GPIOx_AFRH

	Alternate Function Mode 7 is avaliable for USART1. 
	*/
	GPIOB->AFR[0] &= ~(15UL << (4 * 6));	// PB6 Alternate Function Mode = 0 (0000)
	GPIOB->AFR[0] &= ~(15UL << (4 * 7));	// PB7 Alternate Function Mode = 0 (0000)
	GPIOB->AFR[0] |=  ( 7UL << (4 * 6));	// PB6 Alternate Function Mode = 7 (0111)
	GPIOB->AFR[0] |=  ( 7UL << (4 * 7));	// PB7 Alternate Function Mode = 7 (0111)

	GPIOB->MODER  &= ~( 3UL << (2 * 6));	// Set PB6 as Reset State = 00 (0)
	GPIOB->MODER  &= ~( 3UL << (2 * 7));	// Set PB7 as Reset State = 00 (0)
	GPIOB->MODER  |=  ( 2UL << (2 * 6));	// Set PB6 as Alternate Function Mode = 10 (2)
	GPIOB->MODER  |=  ( 2UL << (2 * 7));	// Set PB7 as Alternate Function Mode = 10 (2)

	/* USART1 Clock Enable */
	RCC->APB2ENR	|=  ( 1UL <<  4);    					 

	/* Set Baudrate */
	if(BAUDRATE == 2400) {
		USART1->BRR	= 0x88B8;				//   2400 Bps
	} else if(BAUDRATE == 9600)   {
		USART1->BRR = 0x222D;				//   9600 Bps
	} else if(BAUDRATE == 19200)  {
		USART1->BRR = 0x1118;				//  19200 Bps
	} else if(BAUDRATE == 38400)  {
		USART1->BRR = 0x88C;				//  38400 Bps
	} else if(BAUDRATE == 57600)  {
		USART1->BRR = 0x5B2;				//  57600 Bps
	} else if(BAUDRATE == 115200) {
		USART1->BRR = 0x2DA;				// 115200 Bps
	} else if(BAUDRATE == 230400) {
		USART1->BRR = 0x16C;				// 230400 Bps
	} else if(BAUDRATE == 460800) {
		USART1->BRR = 0xB6;					// 460800 Bps
	} else if(BAUDRATE == 921600) {
		USART1->BRR = 0x5C;					// 921600 Bps
	}

	/* Set Control Register Data */
	USART1->CR1 |= (1 <<  2);				// USART_CR1_RE - Receiver Enable
	USART1->CR1	|= (1 <<  3);				// USART_CR1_TE - Transmitter Enable
	USART1->CR1	|= (1 <<  5);				// USART_CR1_RXNEIE - RXNE Interrupt Enable
	USART1->CR1	|= (1 << 13);				// USART_CR1_UE - USART Enable

	NVIC->ISER[1]  |= 0x20;					// Enable USART1 Interrupt	

	USART1->SR &= (uint32_t)~(0x40);					// Set Noise Detected Flag to 0
	}	

void USART1_WriteChar(uint8_t character)
{
	USART1->DR = character;
	while(!(USART1->SR & 0x80));			// USART_SR_TXE
}

void USART1_WriteString(uint8_t * string)
{
	while(*string++)
	{
		USART1_WriteChar(*string);
	}
}

void USART1_IRQHandler(void)
{
	uint8_t Receive_Characher;

	/* RXNE handler */
	if (USART1->SR & 0x20)					// USART_SR_RXNE
	{
		Receive_Characher = (USART1->DR & 0xFF);
		USART1_WriteChar(Receive_Characher);
	}
}
