/* Firmware Driver for USART2*/
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

int timestamp = 0;


/*SETUP: connect a jumper wire from PA5 to PA6 */
int main(void)
{
	output_compare_mode_pa5();
	input_capture_mode_pa6();
	while(1)
	{
		while(!(TIM3->SR & CC1IF))
		{

		}

		timestamp = TIM3->CCR1;



	}


}
