/*
 * 010i2c_master_tx_testing.c
 *
 */
#include<stdio.h>
#include <string.h>
#include "stm32f407xx.h"

#define SLAVE_ADDR 0x68
#define MY_ADDRESS SLAVE_ADDR

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}

I2C_Handle_t I2C1Handle;

uint8_t Tx_buf[80] = "STM32 Slave mode testing and testing very long strings hello there";

/*
 * PB6-> SCL
 * PB9-> SDA
 */
void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);

	//SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2CPins);
}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDRESS;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	I2C_Init(&I2C1Handle);
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
	//GPIO_ButtonInit();
	I2C1_GPIOInits();
	I2C1_Inits();

	//I2C IRQ configuration
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	I2C_Slave_EnableDisableCallbackEvents(I2C1, ENABLE);

	I2C_PeripheralControl(I2C1, ENABLE);

	//ACK bit is made 1 after PE=1
	I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

	while(1);

	return 0;
}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{
	static uint8_t commandCode = 0;
	static uint8_t Cnt = 0;

	if (AppEv == I2C_EV_DATA_REQ) {
		//Master wants some data, slave has to send it
		if (commandCode == 0x51) {
			//send the length information to master
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*)Tx_buf));
		} else if (commandCode == 0x52) {
			//send the contents of Tx_buf
			I2C_SlaveSendData(pI2CHandle->pI2Cx, Tx_buf[Cnt++]);
		}
	} else if (AppEv == I2C_EV_DATA_RCV) {
		//Data is waiting for the slave to read, slave has to read it
		commandCode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);

	} else if (AppEv == I2C_ERROR_AF) {
		//This happens only during slave Txing
		//Master has sent the NACK, so slave understands that master doesn't need
		//more data
		commandCode = 0xff;
		Cnt = 0;
	} else if (AppEv == I2C_EV_STOP) {
		//This happens only during slave reception
		//Master has ended the I2C communication with the slave

	}
}



