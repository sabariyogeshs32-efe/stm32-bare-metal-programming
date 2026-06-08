#include "stm32f446xx.h"
#define GPTIM2_ENR			(1U<<0)
#define TIM2_EN				(1U<<0)
#define OC1M				((1U<<4) | (1U<<5))
#define CC1E				(1U<<0)
#define GPIOA_EN			(1U<<0)
#include "gptim.h"


void output_compare_mode_pa5(void)
{

	/*For making the PA5 as AF */

/*1.To give the clock source to the AHB1 BUS */

	RCC->AHB1ENR = GPIOA_EN;

/*2.To make the PA5 as the Alternate function Register */

	GPIOA->MODER = ((GPIOA->MODER & ~(1U<<10)) | (1U<<11));

/*3.To set the mode of Alternate function register*/

	GPIOA->AFR[0] = ((GPIOA->AFR[0] & ~(14U<<20)) | (1U<<20));

	/*For the Values to be in TIMER*/

/*1.TO GIVE CLOCK SOURCE TO APB1BUS*/

	RCC->APB1ENR |= GPTIM2_ENR;

/*2.TO SET THE INITIAL VALUES 2. PRESCALER VALUE: */

	TIM2->PSC = 1600 - 1;

/*3.TO SET ARR VALUE*/
	TIM2->ARR = 10000 - 1;


	/*For output compare mode*/

/*1.Set the compare mode register in output mode in channel 1 CH1*/

	TIM2->CCMR1 = OC1M;

/*2.Enable the output compare mode*/

	TIM2->CCER = CC1E;

/* CLEAR COUNTER */

	TIM2->CNT = 0;

/*4.TO SET ENABLE THE TIM2 */

	TIM2->CR1 = TIM2_EN;







}
