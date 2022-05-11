/******************************************************
*
*		NGOHUUDAT
*		COMPUTER ENGINEERING TECHNOLOGY
*		ngohuudat2001@gmail.com
*
*
*		System Configration Functions
*		Version: 0.1
*
*
*		V0.1 - 31.03.2022
*
******************************************************/


#ifndef SYSTEMCLOCK_CONFIG_H_
#define SYSTEMCLOCK_CONFIG_H_

#include "stm32f407xx.h"

// Using HSE with external clock 8MHz
void SysClock_Config(void);
void Delay(uint32_t delay);

#endif	/*SYSTEMCLOCK_CONFIG_H_*/