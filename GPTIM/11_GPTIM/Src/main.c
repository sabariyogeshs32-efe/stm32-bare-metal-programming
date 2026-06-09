#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "systick.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5
#define UIF_FLAG	(1U<<0)
#include "gptim.h"
int main(void)
{
	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	uart2_rxtx_init();
	gptim_init();

	while(1)
	{
/*1.CHECK WHETHER THE COUNT ENDS*/
		while(!(TIM2->SR & UIF_FLAG))
		{

		}
/*2.CLEAR THE FLAG*/
		TIM2->SR &= ~UIF_FLAG;

		GPIOA->ODR ^= LED_PIN;
		printf("1 Second delay has been done Sabari!!! \n");

	}


}
