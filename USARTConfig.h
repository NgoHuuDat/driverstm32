/******************************************************
*
*		NGOHUUDAT
*		COMPUTER ENGINEERING TECHNOLOGY
*		ngohuudat2001@gmail.com
*
*
*		UART Configration Functions
*		Version: 0.1
*
*
*		V0.1 - 31.03.2022
*
******************************************************/


#ifndef UARTX_CONFIG_H_
#define UARTX_CONFIG_H_

	
#include "stm32f407xx.h"

void UART2_Config (void);
void UART2_SendChar (uint8_t character);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);

void USART2_IRQHandler(void);

#endif	/* UARTX_CONFIG_H_ */
