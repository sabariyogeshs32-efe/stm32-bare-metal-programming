#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5



static void dma_callback(void);
int main(void)
{
	char msg[18] = "Hello From F446RE";
	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	uart2_tx_init();
	dma_usart2_dir_m2p_init((uint32_t) msg,(uint32_t)&USART2->DR, 18);

    while(1)
    {
    	}

}

static void dma_callback(void)
{
	GPIOA->ODR |= LED_PIN;
}
void DMA1_Stream6_IRQHandler(void)
{
	/*check whether the interrupt has occured to ensure */
	if(DMA1->HISR & DMA_HTIF6)
	{
		/*1.Clear the interrupt*/
		DMA1->HIFCR |= DMA_HTIF6;

		/*2.Do something...*/
		dma_callback();




	}
	/*check whether the interrupt has occured to ensure */
		if(DMA1->HISR & DMA_TCIF6)
		{
			/*1.Clear the interrupt*/
			DMA1->HIFCR |= DMA_TCIF6;

			/*2.Do something...*/
			GPIOA->ODR &= ~LED_PIN;




		}
}






