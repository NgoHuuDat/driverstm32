/******************************************************
*
*		NGOHUUDAT
*		COMPUTER ENGINEERING TECHNOLOGY
*		ngohuudat2001@gmail.com
*
*
*		I2C Configration Functions
*		Version: 0.1
*
*
*		V0.1 - 31.03.2022
*
******************************************************/


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

	
#include "stm32f407xx.h"


    
void SPI1_Config(void);

void SPI1_Enable(void);
void SPI1_Disable(void);

void CS1_Enable(void);
void CS1_Disable(void);

void SPI1_Transmit(uint8_t *data, int size);
void SPI1_Receive(uint8_t *data, int size);


#endif	/* SPI_CONFIG_H_ 