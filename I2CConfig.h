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


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

	
#include "stm32f407xx.h"


    
void I2C1_Config(void);

void I2C1_Start(void);
void I2C1_Stop(void);

void I2C1_Address(uint32_t address);

void I2C1_Write(uint32_t data);
void I2C1_Read(uint8_t address, uint8_t *buffer, uint8_t size);


#endif	/* I2C_CONFIG_H_ 