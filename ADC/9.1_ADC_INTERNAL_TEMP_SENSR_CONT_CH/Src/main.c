/* main.c*/
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5

uint32_t sensor_value;
float int_temp;
int main(void)
{

	uart2_tx_init();
	adc1_int_temp_snsr_init();


	start_of_convertion();

    while(1)
    {


    	sensor_value = read_value();
    	int_temp = calculate_temperature(sensor_value);

    	printf("!!!The Internal Tempeerature Sensor reading is: %.2f C\n\r",int_temp);
    }
}

