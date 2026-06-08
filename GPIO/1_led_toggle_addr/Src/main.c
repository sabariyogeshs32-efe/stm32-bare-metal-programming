//#include "stm32f4xx.h"
#define PERIPHERAL_BASE     		(0x40000000UL)
#define AHB1BUS_OFFSET 			    (0x00020000UL)
#define AHB1BUS_BASE 				(PERIPHERAL_BASE + AHB1BUS_OFFSET)

#define GPIOA_OFFSET				(0x000000000UL)
#define GPIOA_BASE					(AHB1BUS_BASE + GPIOA_OFFSET)

#define RCC_OFFSET					(0x00003800UL)
#define RCC_BASE 					(AHB1BUS_BASE + RCC_OFFSET)

#define GPIOAEN						(1U<<0)
#define PIN5						(1U<<5)
#define LED_PIN						PIN5
#include<stdint.h>
/*
 * 	(1<<10)		//set bit 10 to 1
 * 	&=~(1<<11) //set bit 11 to 0
 */

typedef struct 

{

	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;
#define RCC  	((RCC_TypeDef*)RCC_BASE)
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)

int main(void)
{
//	   /*  1.Enable clock access to GPIOA	        */
//			RCC_AHB1EN_R |= GPIOAEN;
//	   /* 2.Enable PA5 pin as output  				*/
//			GPIOA_MODE_R |= (1U<<10);
//			GPIOA_MODE_R &= ~(1U<<11);
			RCC->AHB1ENR |= GPIOAEN;
			GPIOA->MODER |=(1U<<10);
			GPIOA->MODER &=~(1U<<11);





	while(1)
	{
	   /*	3.Set PA5 to HIGH (1) */
			GPIOA->ODR ^= PIN5;
			// |= -> THIS IS Friendly program...
			for(int i=0;i<10000000;i++)
			{

			}


	}

}
