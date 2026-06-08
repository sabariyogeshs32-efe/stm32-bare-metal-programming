/* Firmware Driver for USART2*/
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"


int main(void)
{

	uart2_tx_init();

    while(1)
    {
    		printf("SABARIIIII YOGESH \n\r");
    		for(int i=0;i<1000000;i++)

    		{

    		}


    	}

}



