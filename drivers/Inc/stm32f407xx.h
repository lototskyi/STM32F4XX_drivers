/*
 * stm32f407xx.h
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

/********************************************START:Processor Specific Details**************************************
 *
 * ARM Cortex Mx processor NVIC ISERx register Addresses
 */
#define NVIC_ISER0					( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1					( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2					( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3					( (__vo uint32_t*)0xE000E10C )

/*
 * ARM Cortex Mx processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0					( (__vo uint32_t*)0XE000E180 )
#define NVIC_ICER1					( (__vo uint32_t*)0xE000E184 )
#define NVIC_ICER2					( (__vo uint32_t*)0xE000E188 )
#define NVIC_ICER3					( (__vo uint32_t*)0xE000E18C )

/*
 * ARM Cortex Mx processor Priority Register Addresses Calculation
 */
#define NVIC_PR_BASE_ADDR			( (__vo uint32_t*)0xE000E400 )

#define NO_PR_BITS_IMPLEMENTED		4

/**
 * base addresses of Flash and SRAM memories
 */
#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U //112KB
#define SRAM2_BASEADDR				0x2001C000U
#define ROM							0x1FFF0000U //system memory
#define SRAM 						SRAM1_BASEADDR

/**
 * AHBx and APBx Bus Peripheral base addresses
 */
#define PERIPH_BASEADDR				0x40000000U
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U

/**
 * Base addresses of peripherals which are hanging on AHB1 bus
 */
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2000)
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)

/**
 * Base addresses of peripherals which are hanging on APB1 bus
 */
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)

/**
 * Base addresses of peripherals which are hanging on APB2 bus
 */
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)


typedef struct {
	__vo uint32_t MODER;					/*!< GPIO port mode register,					Address offset: 0x00	*/
	__vo uint32_t OTYPER;					/*!< GPIO port output type register				Address offset: 0x04	*/
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];					/*!< AFR[0] : GPIO alternate function low register, AFR[1] : GPIO alternate function high register,				Address offset: 0x20-0x24	*/
} GPIO_RegDef_t;

/**
 * peripheral register definition structure for RCC
 */
typedef struct {
	__vo uint32_t CR;						/*<! Address offset: 0x00 */
	__vo uint32_t PLLCFGR;					/*<! Address offset: 0x04 */
	__vo uint32_t CFGR;						/*<! Address offset: 0x08 */
	__vo uint32_t CIR;						/*<! Address offset: 0x0C */
	__vo uint32_t AHB1RSTR;					/*<! Address offset: 0x10 */
	__vo uint32_t AHB2RSTR;					/*<! Address offset: 0x14 */
	__vo uint32_t AHB3RSTR;					/*<! Address offset: 0x18 */
	uint32_t RESERVED0;						/*<! Reserved: 		 0x1C */
	__vo uint32_t APB1RSTR;					/*<! Address offset: 0x20 */
	__vo uint32_t APB2RSTR;					/*<! Address offset: 0x24 */
	uint32_t RESERVED1[2];					/*<! Reserved: 		 0x28-0x2C */
	__vo uint32_t AHB1ENR;					/*<! Address offset: 0x30 */
	__vo uint32_t AHB2ENR;					/*<! Address offset: 0x34 */
	__vo uint32_t AHB3ENR;					/*<! Address offset: 0x38 */
	__vo uint32_t RESERVED2;				/*<! Reserved: 		 0x3C */
	__vo uint32_t APB1ENR;					/*<! Address offset: 0x40 */
	__vo uint32_t APB2ENR;					/*<! Address offset: 0x44 */
	uint32_t RESERVED3[2];					/*<! Reserved: 		 0x48-0x4C */
	__vo uint32_t AHB1LPENR;				/*<! Address offset: 0x50 */
	__vo uint32_t AHB2LPENR;				/*<! Address offset: 0x54 */
	__vo uint32_t AHB3LPENR;				/*<! Address offset: 0x58 */
	uint32_t RESERVED4;						/*<! Reserved: 		 0x5C */
	__vo uint32_t APB1LPENR;				/*<! Address offset: 0x60 */
	__vo uint32_t APB2LPENR;				/*<! Address offset: 0x64 */
	uint32_t RESERVED5[2];					/*<! Reserved: 		 0x68-0x6C */
	__vo uint32_t BDCR;						/*<! Address offset: 0x70 */
	__vo uint32_t CSR;						/*<! Address offset: 0x74 */
	uint32_t RESERVED6[2];					/*<! Reserved: 		 0x78-0x7C */
	__vo uint32_t SSCGR;					/*<! Address offset: 0x80 */
	__vo uint32_t PLLI2SCFGR;				/*<! Address offset: 0x84 */
} RCC_RegDef_t;

/**
 * peripheral register definition structure for EXTI
 */
typedef struct {
	__vo uint32_t IMR;					/*!< Interrupt mask register,					Address offset: 0x00	*/
	__vo uint32_t EMR;					/*!< Event mask register,						Address offset: 0x04	*/
	__vo uint32_t RTSR;					/*!< Rising trigger selection register,			Address offset: 0x08	*/
	__vo uint32_t FTSR;					/*!< Falling trigger selection register,		Address offset: 0x0C	*/
	__vo uint32_t SWIER;				/*!< Software interrupt event register,		Address offset: 0x10	*/
	__vo uint32_t PR;					/*!< Pending register,							Address offset: 0x14	*/
} EXTI_RegDef_t;

/**
 * peripheral register definition structure for SYSCFG
 */
typedef struct {
	__vo uint32_t MEMRMP;				/*!< SYSCFG memory remap register,								Address offset: 0x00		*/
	__vo uint32_t PMC;					/*!< SYSCFG peripheral mode configuration register,				Address offset: 0x04		*/
	__vo uint32_t EXTICR[4];			/*!< SYSCFG external interrupt configuration register 1,2,3,4,	Address offset: 0x08-0x14	*/
	uint32_t RESERVED[2];				/*!< Reserved, 													Address offset:	0x18-0x1C  	*/
	__vo uint32_t CMPCR;				/*!< Compensation cell control register,						Address offset: 0x20		*/
} SYSCFG_RegDef_t;

/**
 * peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 */
#define GPIOA 						( (GPIO_RegDef_t*) GPIOA_BASEADDR )
#define GPIOB 						( (GPIO_RegDef_t*) GPIOB_BASEADDR )
#define GPIOC 						( (GPIO_RegDef_t*) GPIOC_BASEADDR )
#define GPIOD 						( (GPIO_RegDef_t*) GPIOD_BASEADDR )
#define GPIOE 						( (GPIO_RegDef_t*) GPIOE_BASEADDR )
#define GPIOF 						( (GPIO_RegDef_t*) GPIOF_BASEADDR )
#define GPIOG 						( (GPIO_RegDef_t*) GPIOG_BASEADDR )
#define GPIOH 						( (GPIO_RegDef_t*) GPIOH_BASEADDR )
#define GPIOI 						( (GPIO_RegDef_t*) GPIOI_BASEADDR )

#define RCC							( (RCC_RegDef_t*) RCC_BASEADDR )
#define EXTI						( (EXTI_RegDef_t*) EXTI_BASEADDR )
#define SYSCFG						( (SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

/**
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()				( RCC->AHB1ENR |= (1 << 0) )
#define GPIOB_PCLK_EN()				( RCC->AHB1ENR |= (1 << 1) )
#define GPIOC_PCLK_EN()				( RCC->AHB1ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()				( RCC->AHB1ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()				( RCC->AHB1ENR |= (1 << 4) )
#define GPIOF_PCLK_EN()				( RCC->AHB1ENR |= (1 << 5) )
#define GPIOG_PCLK_EN()				( RCC->AHB1ENR |= (1 << 6) )
#define GPIOH_PCLK_EN()				( RCC->AHB1ENR |= (1 << 7) )
#define GPIOI_PCLK_EN()				( RCC->AHB1ENR |= (1 << 8) )

/**
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()				( RCC->APB1ENR |= (1 << 21) )
#define I2C2_PCLK_EN()				( RCC->APB1ENR |= (1 << 22) )
#define I2C3_PCLK_EN()				( RCC->APB1ENR |= (1 << 23) )

/**
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()				( RCC->APB2ENR |= (1 << 12) )

/**
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN()			( RCC->APB2ENR |= (1 << 4)  )
#define USART2_PCLK_EN()			( RCC->APB1ENR |= (1 << 17) )
#define USART3_PCLK_EN()			( RCC->APB1ENR |= (1 << 18) )
#define UART4_PCLK_EN()				( RCC->APB1ENR |= (1 << 19) )
#define UART5_PCLK_EN()				( RCC->APB1ENR |= (1 << 20) )
#define USART6_PCLK_EN()			( RCC->APB2ENR |= (1 << 5)  )

/**
 * Clock Enable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()			( RCC->APB2ENR |= (1 << 14) )

/**
 * Clock Disable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 0) )
#define GPIOB_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 4) )
#define GPIOF_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 5) )
#define GPIOG_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 6) )
#define GPIOH_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 7) )
#define GPIOI_PCLK_DI()				( RCC->AHB1ENR &= ~(1 << 8) )

/**
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()				( RCC->APB1ENR &= ~(1 << 21) )
#define I2C2_PCLK_DI()				( RCC->APB1ENR &= ~(1 << 22) )
#define I2C3_PCLK_DI()				( RCC->APB1ENR &= ~(1 << 23) )

/**
 * Clock Disable Macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()				( RCC->APB2ENR &= ~(1 << 12) )

/**
 * Clock Disable Macros for USARTx peripherals
 */
#define USART1_PCLK_DI()			( RCC->APB2ENR &= ~(1 << 4)  )
#define USART2_PCLK_DI()			( RCC->APB1ENR &= ~(1 << 17) )
#define USART3_PCLK_DI()			( RCC->APB1ENR &= ~(1 << 18) )
#define UART4_PCLK_DI()				( RCC->APB1ENR &= ~(1 << 19) )
#define UART5_PCLK_DI()				( RCC->APB1ENR &= ~(1 << 20) )
#define USART6_PCLK_DI()			( RCC->APB2ENR &= ~(1 << 5)  )

/**
 * Clock Disable Macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()			( RCC->APB2ENR &= ~(1 << 14) )

/**
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 0)); ( RCC->AHB1RSTR &= ~(1 << 0));} while(0)
#define GPIOB_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 1)); ( RCC->AHB1RSTR &= ~(1 << 1));} while(0)
#define GPIOC_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 2)); ( RCC->AHB1RSTR &= ~(1 << 2));} while(0)
#define GPIOD_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 3)); ( RCC->AHB1RSTR &= ~(1 << 3));} while(0)
#define GPIOE_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 4)); ( RCC->AHB1RSTR &= ~(1 << 4));} while(0)
#define GPIOF_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 5)); ( RCC->AHB1RSTR &= ~(1 << 5));} while(0)
#define GPIOG_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 6)); ( RCC->AHB1RSTR &= ~(1 << 6));} while(0)
#define GPIOH_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 7)); ( RCC->AHB1RSTR &= ~(1 << 7));} while(0)
#define GPIOI_REG_RESET()			do{( RCC->AHB1RSTR |= (1 << 8)); ( RCC->AHB1RSTR &= ~(1 << 8));} while(0)

#define GPIO_BASEADDR_TO_CODE(x)	( (x == GPIOA) ? 0 :\
									  (x == GPIOB) ? 1 :\
									  (x == GPIOC) ? 2 :\
									  (x == GPIOD) ? 3 :\
									  (x == GPIOE) ? 4 :\
									  (x == GPIOF) ? 5 :\
									  (x == GPIOG) ? 6 :\
									  (x == GPIOH) ? 7 :\
									  (x == GPIOI) ? 8 :0 )

/**
 * IRQ(Interrupt request) Numbers of STM32F407x MCU
 */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

/**
 * IRQ priority
 */
#define NVIC_IRQ_PRI0				0
#define NVIC_IRQ_PRI1				1
#define NVIC_IRQ_PRI2				2
#define NVIC_IRQ_PRI3				3
#define NVIC_IRQ_PRI4				4
#define NVIC_IRQ_PRI5				5
#define NVIC_IRQ_PRI6				6
#define NVIC_IRQ_PRI7				7
#define NVIC_IRQ_PRI8				8
#define NVIC_IRQ_PRI9				9
#define NVIC_IRQ_PRI10				10
#define NVIC_IRQ_PRI11				11
#define NVIC_IRQ_PRI12				12
#define NVIC_IRQ_PRI13				13
#define NVIC_IRQ_PRI14				14
#define NVIC_IRQ_PRI15				15


//some generic macros
#define ENABLE 						1
#define DISABLE 					0
#define SET 						ENABLE
#define RESET 						DISABLE
#define GPIO_PIN_SET 				SET
#define GPIO_PIN_RESET 				RESET

#include "stm32f407xx_gpio_driver.h"

#endif /* INC_STM32F407XX_H_ */
