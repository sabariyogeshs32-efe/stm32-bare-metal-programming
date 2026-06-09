/* Firmware Driver for USART2*/
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5

uint32_t sensor_value;
int main(void)
{

	uart2_tx_init();
	adc1_init();


    while(1)
    {
    	start_of_convertion();

    	sensor_value = read_value();

    	printf("The Sensor value is: %d\n\r",(int)sensor_value);
    }
}

