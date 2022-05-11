#include"I2CConfig.h"

void I2C1_Config(void)
{	
	// Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1UL<<21);  // enable I2C CLOCK
	RCC->AHB1ENR |= (1UL<<1);  // Enable GPIOB CLOCK
	
	//  Configure the I2C PINs for ALternate Functions
	GPIOB->MODER |= (2UL<<16) | (2UL<<18);  // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
	GPIOB->OTYPER |= (1UL<<8) | (1UL<<9);  //  Bit8=1, Bit9=1  output open drain
	GPIOB->OSPEEDR |= (3UL<<16) | (3UL<<18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
	GPIOB->PUPDR |= (1UL<<16) | (1UL<<18);  // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
	GPIOB->AFR[1] |= (4UL<<0) | (4UL<<4);  // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9
	
	// Reset the I2C
	I2C1->CR1 |= (1UL<<15);  // reset the I2C
	I2C1->CR1 &= ~(1UL<<15);  // Normal operation
	
	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2C1->CR2 |= (42UL<<0);  // PCLK1 FREQUENCY in MHz
	
	// Configure the clock control registers
	I2C1->CCR = 210UL<<0;  // check calculation in PDF ** STANDARD MODE **
	
	// Configure the rise time register
	I2C1->TRISE = 43UL;  // check PDF again
	
	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1UL<<0);  // Enable I2C
}

void I2C1_Start(void) 
{	
	I2C1->CR1 |= (1UL<<10);  // Enable the ACK
	I2C1->CR1 |= (1UL<<8);  // Generate START
}

void I2C1_Stop(void)
{	
	uint8_t temp;
	I2C1->CR1 &= ~(1UL<<10);  // clear the ACK bit 
	temp = (uint8_t)(I2C1->SR1 | I2C1->SR2);  // read SR1 and SR2 to clear the ADDR bit.... EV6 condition
	I2C1->CR1 |= (1UL<<9);  // Stop I2C
}

void I2C1_Address(uint32_t address)
{
	uint8_t temp;
	I2C1->DR = address;  //  send the address
	while (!(I2C1->SR1 & (1UL<<1)));  // wait for ADDR bit to set
	temp = (uint8_t)(I2C1->SR1 | I2C1->SR2);  // read SR1 and SR2 to clear the ADDR bit
}


void I2C1_Write(uint32_t data)
{
	while (!(I2C1->SR1 & (1UL<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1UL<<2)));  // wait for BTF bit to set
}

void I2C1_Read(uint8_t address, uint8_t *buffer, uint8_t size)
{
	unsigned remaining = size;
	
    I2C1_Address(address);

	if (size == 1)
	{
		I2C1_Stop();
	
		while (!(I2C1->SR1 & (1UL<<6)));  // wait for RxNE to set	
		buffer[size-remaining] = (uint8_t)I2C1->DR;  // Read the data from the DATA REGISTER	
	}	
	else 
	{
		while (remaining>2)
		{
			while (!(I2C1->SR1 & (1UL<<6)));  // wait for RxNE to set
			buffer[size-remaining] = (uint8_t)I2C1->DR;  // copy the data into the buffer			
			I2C1->CR1 |= 1UL<<10;  // Set the ACK bit to Acknowledge the data received
			remaining--;
		}
		
		// Read the SECOND LAST BYTE
		while (!(I2C1->SR1 & (1UL<<6)));  // wait for RxNE to set
		buffer[size-remaining] = (uint8_t)I2C1->DR;
	
		I2C1_Stop();
		
		remaining--;
		
		// Read the Last BYTE
		while (!(I2C1->SR1 & (1<<6)));  // wait for RxNE to set
		buffer[size-remaining] = (uint8_t)I2C1->DR;  // copy the data into the buffer
	}
}
