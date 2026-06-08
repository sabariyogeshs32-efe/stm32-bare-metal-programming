/* Firmware Driver for USART2*/
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5

char key;
static void usart2_callback(void);
int main(void)
{
	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	uart2_rxtx_init();
	uart2_interrupt_handler_init();

    while(1)
    {
    	}

}

static void usart2_callback(void)
{
	key=uart2_read();

	if(key == 'L')
	    {
	    	GPIOA->ODR |= LED_PIN;
	    }
	    else
	    {
	    	GPIOA->ODR &= ~LED_PIN;    }
	    }


void USART2_IRQHandler(void)
{
	/*Check if RXNE is set */
	if(USART2->SR & SR_RXNE)
	{
		/*Do Something...*/
		usart2_callback();
	}
}


/*
 * #include "stm32f446xx.h"
#define GPIOAEN 	(1U<<0)
#define PIN5 	(1U<<5)
#define LED_PIN	PIN5
int main(void)
{

		RCC->AHB1ENR |=GPIOAEN;
		GPIOA->MODER |=(1U<<10);
		GPIOA->MODER &=~(1U<<11);

    while(1)
    {
    	 GPIOA->ODR ^= LED_PIN;
    	for(int i=0;i<100000;i++)
    	{

    	}

    }
}
 *
 */

