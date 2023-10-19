/*
 * 007spi_txonly_arduino.c
 */

#include <string.h>
#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

//
/*
 * PB12 --> SPI2_NSS
 * PB13 --> SPI2_SCLK
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * ALT function mode: 5
 */

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_ClkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2Handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
//	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);
}

int main(void)
{
	char user_data[] = "array_intersect() returns an array containing all the values of array that are present in all the arguments. Note that keys are preserved.";

	GPIO_ButtonInit();

	SPI2_GPIOInits();

	SPI2_Inits();

	/*
	 * making SSOE 1 does NSS output enable.
	 * The NSS pin is automatically managed by hardware
	 * i.e. when SPE=1, NSS will be pulled to low
	 * and NSS pin will be high when SPE=0
	 */
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1) {
		while(! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));

		delay();

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		//send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2, &dataLen, 1);

		SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI2, DISABLE);
	}

	return 0;
}
