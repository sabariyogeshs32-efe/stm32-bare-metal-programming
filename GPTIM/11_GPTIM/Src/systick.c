#include "stm32f446xx.h"
#define SYSTICK_VALUE			(16000)
#define SYSTICK_EN				(1U<<0)
#define SYSTICK_INT_CLK			(1U<<2)
#define SYSTICK_COUNT_FLG		(1U<<16)


void SysTick_ms_Delay(int delay)
{
		/* 1.Load with the desired Value in STRVR Register */
	 /* for 1msecond delay N=16000 we have calculated earlier */

		SysTick->LOAD = SYSTICK_VALUE;
		/* 2.CLEAR THE CURRENT VALUE REGISTER OF SYSTICK */

		SysTick->VAL = 0;

		/* 3.Enable the SYSTICK Timer and configure the clock whether internal or reference clock to be given for systick Timer 0-> EXTERNAL CLOCK SOURCE 1->PROCESSOR CLOCK SOURCE*/

		SysTick->CTRL = SYSTICK_EN | SYSTICK_INT_CLK;

		/* RIGHT NOW THE TIMER IS STARTED DOWN COUNTING IT WAS SET TO BE ENABLED AND CLOCK WAS CONFIGURED! */

		/* 4.Now we have run counter as much times we wanted it to count.. repeating of 1ms for n value! */

		for(int i=0; i<delay; i++)
		{
			while((SysTick->CTRL & SYSTICK_COUNT_FLG)==0)
					{
				/* IT Will wait until the count flag has been set */
					}

		}

		/* 5.reset the Value Register and Load Register */

		SysTick->LOAD = 0;
		SysTick->VAL = 0;
}
