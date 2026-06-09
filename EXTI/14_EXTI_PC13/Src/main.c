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
#include "input_capture_mode_ccm1.h"
#include "exti.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5





int main(void)
{

	exti_pc13_init();

	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	uart2_rxtx_init();

	while(1)
	{




	}


}

static void exti_callback(void)
{
	printf("BTN IS PRESSED... \n");
	GPIOA->ODR ^= LED_PIN;
	//printf("1 Second delay has been done Sabari!!! \n");

}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & EXTI_13) != 0)
	{
		/*Clear the PR Flag*/
		EXTI->PR |= EXTI_13;
		/*Do Something...*/
		exti_callback();

	}
}
