#include "stm32f446xx.h"
#include "exti.h"
#define GPIOC_EN	(1U<<2)
#define SYSCFG_EN	(1U<<14)
#define EXTI_13		(1U<<13)



void exti_pc13_init(void)

{
	/*1.Disable Global Interrupts*/
	__disable_irq();

	/*2.Enable clock for GPIOC input button for interrupt*/
	RCC->AHB1ENR |= GPIOC_EN;

	/*3.Make the PC13 as input PIN button for interrupt*/
	GPIOC->MODER &= (1U<<26);
	GPIOC->MODER &= (1U<<27);

	/*4.Enable the clock for the SYSCFG*/
	RCC->APB2ENR |= SYSCFG_EN;

	/*5.Select the PortC in the EXTI15_10_IRQ IN EXTICR */
	SYSCFG->EXTICR[3] = ((SYSCFG->EXTICR[3] & ~(13U<<4)) | (1U<<5));


	/*6.Unmask the EXTI13 IN NVIC*/
	EXTI->IMR |= EXTI_13;

	/*7.Select Rising or Falling Edge Triggered Interrupt!!!*/
	EXTI->FTSR |= EXTI_13;
	//EXTI->FTSR |= EXTI_13;

	/*7.Enable the NVIC Interrupt*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*8.Disable the Global Interrupt*/
	__enable_irq();

}
