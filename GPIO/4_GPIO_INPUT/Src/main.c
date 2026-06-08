#include "stm32f446xx.h"
#define GPIOAEN 	(1U<<0)
#define GPIOCEN		(1U<<2)
#define PIN5 	(1U<<5)
#define LED_PIN	PIN5
int main(void)
{

		RCC->AHB1ENR |=GPIOAEN;
		RCC->AHB1ENR |=GPIOCEN;
		GPIOA->MODER |=(1U<<10);
		GPIOA->MODER &=~(1U<<11);
		GPIOC->MODER &=~(1U<<26);
		GPIOC->MODER &=~(1U<<27);


    while(1)
    {
    	volatile uint32_t inp=GPIOC->IDR;
    	if(inp & (1<<13))
    	{
    		GPIOA->BSRR =(1U<<21);
    		for(int i=0;i<100000;i++)
    		    	{

    		    	}
    	}
    	else
    	{	GPIOA->BSRR =(1U<<5);
    	for(int i=0;i<100000;i++)
    	    	{

    	    	}

    	}
    }
}
