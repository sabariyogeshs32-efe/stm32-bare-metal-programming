#include "stm32f446xx.h"
#define GPTIM2_ENR			(1U<<0)
#define TIM2_EN				(1U<<0)
#include "gptim.h"

void gptim_init(void)
{
/*1.TO GIVE CLOCK SOURCE TO APB1BUS*/

	RCC->APB1ENR |= GPTIM2_ENR;

/*2.TO SET THE INITIAL VALUES 2. PRESCALER VALUE: */

	TIM2->PSC = 3200 - 1;

/*3.TO SET ARR VALUE*/
	TIM2->ARR = 10000 - 1;

/* CLEAR COUNTER */
	TIM2->CNT = 0;
/*4.TO SET ENABLE THE TIM2 */
	TIM2->CR1 = TIM2_EN;







}
