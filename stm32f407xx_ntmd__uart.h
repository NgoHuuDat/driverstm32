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


#ifndef __STM32F407xx_NTMD_UART_H__
#define __STM32F407xx_NTMD_UART_H__

	
#include "stm32f407xx.h"

void USART1_Init(uint32_t BAUDRATE);
void USART1_WriteChar(uint8_t character);
void USART1_WriteString(uint8_t * string);

void USART1_IRQHandler(void);





 /*******************************************************
	*
	* UART Init Structure definition
	*
*****************************************************/
typedef struct
{
  uint32_t BaudRate;        // BaudRate ** 2400 || 9600 || 19200 || 38400 || 57600 || 115200 || 230400 || 460800 || 921600 **

  uint32_t WordLength;      // Data bits transmitted or received in a frame **  0 -> 1 Start bit, 8 Data bits, n Stop bit || 1 -> 1 Start bit, 9 Data bits, n Stop bit **

  uint32_t StopBits;        // STOP bits **  00: 1 stopbit || 01: 0.5 stopbit || 10: 2 stopbit || 11: 1.5 stopbit ** 

  uint32_t Parity;          // Parity control enable ** 0: Disabled || 1: Enabled **

  uint32_t Mode;            // Receive or Transmit mode is enabled or disabled ** 0: Disabled || 1: Enabled **

  uint32_t HwFlowCtl;       // Hardware flow control mode is enabled or disabled ** CR3 -> CTSE and RTSE **

  uint32_t OverSampling;    // Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8) ** 0: oversampling by 16 || 1: oversampling by 8 **
} UART_InitTypeDef;


 /*******************************************************
	*
	* UART handle Structure definition
	*
*****************************************************/

typedef struct
{
  USART_TypeDef                 *Instance;        //	UART registers base address

  UART_InitTypeDef              Init;             // 	UART communication parameters     

  uint8_t                       *pTxBuffPtr;      // 	Pointer to UART Tx transfer Buffer 

  uint16_t                      TxXferSize;       // 	UART Tx Transfer size

  volatile uint16_t                 TxXferCount;      // 	UART Tx Transfer Counter

  uint8_t                       *pRxBuffPtr;      // 	Pointer to UART Rx transfer Buffer 

  uint16_t                      RxXferSize;       //	UART Rx Transfer size              

  volatile uint16_t                 RxXferCount;      //	UART Rx Transfer Counter           

  volatile uint32_t                 ErrorCode;        //	UART Error code                   

} UART_HandleTypeDef;







#endif	/* __STM32F407xx_NTMD_UART_H__ */
