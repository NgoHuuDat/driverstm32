#include"SPIConfig.h"

void SPI1_Config(void)
{
    // Enable the SPI CLOCK and GPIO CLOCK
    RCC->APB2ENR |= (1UL<<12);  // Enable SPI1 CLock
	RCC->AHB1ENR |= (1<<0);  // Enable GPIOA Clock
	
    //  Configure the SPI PINs for ALternate Functions
	GPIOA->MODER |= (2<<10)|(2<<12)|(2<<14)|(1<<18);  // Alternate functions for PA5, PA6, PA7 and Output for PA9
	GPIOA->OSPEEDR |= (3<<10)|(3<<12)|(3<<14)|(3<<18);  // HIGH Speed for PA5, PA6, PA7, PA9
	GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);   // AF5(SPI1) for PA5, PA6, PA7

    // Configure the SPI
    SPI1->CR1 |= (1UL<<0);   // CPOL=1 ** CK to 1 when idle **
    SPI1->CR1 |= (1UL<<1);  // CPHA = 1 ** The second clock transition is the first data capture edge **
    SPI1->CR1 |= (1UL<<2);  // Master Mode ** Master configuration = 1 | Slave configuration = 0**
    SPI1->CR1 |= (3UL<<3);  // BR[2:0] = 011: fPCLK/16, PCLK2 = 84MHz, SPI clk = 5.25MHz  
    SPI1->CR1 &= ~(1UL<<7);  // LSBFIRST = 0 ** MSB first ** 

    SPI1->CR1 |= (1UL<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management  

    SPI1->CR1 &= ~(1UL<<10);  // RXONLY = 0 ** Full-duplex | RXONLY = 1 Receive only ** 
    SPI1->CR1 &= ~(1UL<<11);  // DFF=0  ** 8 bit data | DFF = 1 16 bit data **
}

void SPI1_Enable(void)
{
    SPI1->CR1 |= (1UL<<6);   // SPE=1, Peripheral enabled
}

void SPI1_Disable(void)
{
    SPI1->CR1 &= ~(1UL<<6);   // SPE=0, Peripheral Disabled
}

void CS1_Enable(void)
{
    GPIOA->BSRR |= (1UL<<9)<<16;
}

void CS1_Disable(void)
{
    GPIOA->BSRR |= (1UL<<9);
}


void SPI1_Transmit(uint8_t *data, int size)
{
    int i=0;
	while (i<size)
	{
	   while (!((SPI1->SR)&(1UL<<1)));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}	
	
	while (!((SPI1->SR)&(1UL<<1)));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&(1UL<<7)));  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
    uint8_t temp;
	temp = (uint8_t)SPI1->DR;
	temp = (uint8_t)SPI1->SR;
}

void SPI1_Receive(uint8_t *data, int size)
{
    while (size)
	{
		while (((SPI1->SR)&(1UL<<7)));  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) &(1UL<<0))){}  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	    *data++ = (uint8_t)(SPI1->DR);
		size--;
	}	
}