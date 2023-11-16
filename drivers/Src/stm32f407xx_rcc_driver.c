/*
 * stm32f407xx_rcc_driver.c
 *
 */

#include "stm32f407xx_rcc_driver.h"


uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB_PreScaler[4] = {2,4,8,16};

uint32_t RCC_GetPLLOutputClock(void)
{
	return 0;
}

uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1, SystemClock;

	uint8_t clksrc, temp, ahbp, apb1p;

	clksrc = (RCC->CFGR >> 2) & 0x3;

	if (clksrc == 0) {
		SystemClock = 16000000;
	} else if (clksrc == 1) {
		SystemClock = 8000000;
	} else if (clksrc == 2) {
		SystemClock = RCC_GetPLLOutputClock();
	}

	//for AHB
	temp = (RCC->CFGR >> 4) & 0xF;

	if (temp < 8) {
		ahbp = 1;
	} else {
		ahbp = AHB_PreScaler[temp-8];
	}

	//for APB1
	temp = (RCC->CFGR >> 10) & 0x7;

	if (temp < 4) {
		apb1p = 1;
	} else {
		apb1p = APB_PreScaler[temp-4];
	}

	pclk1 = (SystemClock / ahbp) / apb1p;

	return pclk1;
}

uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2, SystemClock;

	uint8_t clksrc, temp, ahbp, apb2p;

	clksrc = (RCC->CFGR >> 2) & 0x3;

	if (clksrc == 0) {
		SystemClock = 16000000;
	} else if (clksrc == 1) {
		SystemClock = 8000000;
	} else if (clksrc == 2) {
		SystemClock = RCC_GetPLLOutputClock();
	}

	//for AHB
	temp = (RCC->CFGR >> 4) & 0xF;

	if (temp < 8) {
		ahbp = 1;
	} else {
		ahbp = AHB_PreScaler[temp-8];
	}

	//for APB2
	temp = (RCC->CFGR >> 13) & 0x7;

	if (temp < 4) {
		apb2p = 1;
	} else {
		apb2p = APB_PreScaler[temp-4];
	}

	pclk2 = (SystemClock / ahbp) / apb2p;

	return pclk2;
}

