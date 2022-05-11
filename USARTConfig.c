#include"USARTConfig.h"

void UART2_Config (void)
{
		/******* USING UART2 ********
	
	1. Enable the UART CLOCK and GPIO CLOCK
	2. Configure the UART PINs for ALternate Functions
	3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	4. Program the M bit in USART_CR1 to define the word length.
	5. Select the desired baud rate using the USART_BRR register.
	6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register

	********************************/
	
	// Enable the UART CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1UL<<17);  // Enable UART2 CLOCK
	RCC->AHB1ENR |= (1UL<<0); // Enable GPIOA CLOCK
	
	// Configure the UART PINs for ALternate Functions
	GPIOA->MODER |= (2UL<<4);  // Bits (5:4)= 1:0 --> Alternate Function for Pin PA2
	GPIOA->MODER |= (2UL<<6);  // Bits (7:6)= 1:0 --> Alternate Function for Pin PA3
	
	GPIOA->OSPEEDR |= (2UL<<4) | (2UL<<6);  // Bits (5:4)= 1:1 and Bits (7:6)= 1:1 --> High Speed for PIN PA2 and PA3
	
	GPIOA->AFR[0] |= (7UL<<8);  // Bytes (11:10:9:8) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PA2 (AFR[0] = AFRL)
	GPIOA->AFR[0] |= (7UL<<12); // Bytes (15:14:13:12) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PA3

	
	// Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USART2->CR1 = 0UL;  // clear all
	USART2->CR1 |= (1UL<<13);  // UE = 1  Enable USART
	
	// Program the M bit in USART_CR1 to define the word length.
	USART2->CR1 &= ~(1UL<<12);  // M =0; 8 bit word length
	
	// Select the desired baud rate using the USART_BRR register.
	USART2->BRR = ((0<<0) | (22UL<<4));   // Baud rate of 115200, PCLK1 at 42MHz
	
	// Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
	USART2->CR1 |= (1UL<<2); // RE=1.. Enable the Receiver
	USART2->CR1 |= (1UL<<3);  // TE=1.. Enable Transmitter
	
	USART2->CR1	|= (1UL<<5); // RXNEIE - RXNE Interrupt Enable
	NVIC_SetPriority (USART2_IRQn, 1);
	NVIC_EnableIRQ(USART2_IRQn);  // Enable USART2 Interrupt	
	NVIC_ClearPendingIRQ(USART2_IRQn); // Clear Pending interrupt
}


void UART2_SendChar (uint8_t character)
{
		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
	
	USART2->DR = character; // load the data into DR register
	while (!(USART2->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}
	
void UART2_SendString (char *string)
{
	while (*string)
		UART_SendChar (*string++);
}

uint8_t UART2_GetChar (void)
{
			/*********** STEPS FOLLOWED *************
	
	Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	Read the data from USART_DR  Register. This also clears the RXNE bit
	
	****************************************/

	uint8_t character;
	
	while (!(USART2->SR & (1<<5)));  // wait for RXNE bit to set
	character = (USART2->DR & 0xFF);  // Read the data. This clears the RXNE also
	return character;
}

void USART2_IRQHandler(void)
{
	uint8_t Character;

	/* RXNE handler */
	if (USART2->SR & (1<<5))					// USART_SR_RXNE
	{
		Character = (USART2->DR & 0xFF);
		UART_SendChar(Character);
	}
}