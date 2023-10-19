/*
 * 008spi_cmd_handling.c
 *
 */
#include<stdio.h>
#include <string.h>
#include "stm32f407xx.h"

extern void initialise_monitor_handles();

//command codes
#define COMMAND_LED_CTRL				0x50
#define COMMAND_SENSOR_READ				0x51
#define COMMAND_LED_READ				0x52
#define COMMAND_PRINT					0x53
#define COMMAND_ID_READ					0x54

#define LED_ON							1
#define LED_OFF							0

//arduino analog pins
#define ANALOG_PIN0						0
#define ANALOG_PIN1						1
#define ANALOG_PIN2						2
#define ANALOG_PIN3						3
#define ANALOG_PIN4						4
#define ANALOG_PIN5						5

//arduino led
#define LED_PIN							9

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

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if (ackbyte == 0xF5) {
		//ack
		return 1;
	}

	return 0;
}

int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	initialise_monitor_handles();

	printf("Application is running\n");

	GPIO_ButtonInit();

	SPI2_GPIOInits();

	SPI2_Inits();

	printf("SPI Init.\n");
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

		//1. CMD_LED_CTRL	<pin no(1)>		<value(1)>
		uint8_t commandcode = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];
		SPI_SendData(SPI2, &commandcode, 1);

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//send some dummy bits (1 byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		//read the ack byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if (SPI_VerifyResponse(ackbyte)) {
			//send arguments
			args[0] = LED_PIN;
			args[1] = LED_ON;

			SPI_SendData(SPI2, args, 2);
			printf("COMMAND_LED_CTRL Executed\n");
		}



		//2. CMD_SENSOR_READ	<analog pin number(1) >
		while(! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));

		delay();

		commandcode = COMMAND_SENSOR_READ;
		SPI_SendData(SPI2, &commandcode, 1);

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//send some dummy bits (1 byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		//read the ack byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if (SPI_VerifyResponse(ackbyte)) {
			//send arguments
			args[0] = ANALOG_PIN0;
			SPI_SendData(SPI2, args, 1);

			SPI_ReceiveData(SPI2, &dummy_read, 1);
			delay();
			SPI_SendData(SPI2, &dummy_write, 1);

			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
			printf("COMMAND_SENSOR_READ %d\n", analog_read);
		}

		//3. COMMAND_LED_READ 	<pin no(1)>
		while(! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));
		delay();
		commandcode = COMMAND_LED_READ;
		SPI_SendData(SPI2, &commandcode, 1);

		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if (SPI_VerifyResponse(ackbyte)) {
			args[0] = LED_PIN;
			SPI_SendData(SPI2, args, 1);

			SPI_ReceiveData(SPI2, &dummy_read, 1);
			delay();
			SPI_SendData(SPI2, &dummy_write, 1);

			uint8_t led_status;
			SPI_ReceiveData(SPI2, &led_status, 1);
			printf("COMMAND_LED_READ %d\n", led_status);
		}



		//4. CMD_PRINT 		<len(2)>  <message(len) >

		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_PRINT;

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2,&dummy_read,1);

		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2,&dummy_write,1);

		//read the ack byte received
		SPI_ReceiveData(SPI2,&ackbyte,1);

		uint8_t message[] = "Hello ! How are you ??";
		if (SPI_VerifyResponse(ackbyte)) {
			args[0] = strlen((char*)message);

			//send arguments
			SPI_SendData(SPI2,args,1); //sending length

			//do dummy read to clear off the RXNE
			SPI_ReceiveData(SPI2,&dummy_read,1);

			delay();

			//send message
			for (int i = 0 ; i < args[0] ; i++) {
				SPI_SendData(SPI2,&message[i],1);
				SPI_ReceiveData(SPI2,&dummy_read,1);
			}

			printf("COMMAND_PRINT Executed \n");

		}

		//5. CMD_ID_READ
		//wait till button is pressed
		while (!GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_ID_READ;

		//send command
		SPI_SendData(SPI2, &commandcode, 1);

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);

		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);

		//read the ack byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		uint8_t id[16];
		uint32_t i=0;
		if (SPI_VerifyResponse(ackbyte)) {
			//read 10 bytes id from the slave
			for (  i = 0 ; i < 15 ; i++)	{
				//send dummy byte to fetch data from slave
				SPI_SendData(SPI2, &dummy_write, 1);
				SPI_ReceiveData(SPI2, &id[i], 1);
			}

			id[15] = '\0';

			printf("COMMAND_ID : %s \n",id);

		}



		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI2, DISABLE);

		printf("SPI Communication Closed\n");
	}

	return 0;
}


