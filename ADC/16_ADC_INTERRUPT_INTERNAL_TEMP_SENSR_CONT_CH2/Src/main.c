/* main.c*/
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#define GPIOA_EN	(1U<<0)
#define PA5	        (1U<<5)
#define LED_PIN	     PA5

static void ADC_callback(void);
uint32_t sensor_value;
float int_temp;
int main(void)
{

	uart2_tx_init();
	adc1_int_temp_snsr_init();


	start_of_convertion();

    while(1)
    {



    }
}

static void ADC_callback(void)
{
	sensor_value = ADC1->DR;
	int_temp = calculate_temperature(sensor_value);

	printf("The Internal Tempeeerature Sensor reading is: %.2f C\n\r",int_temp);
}
void ADC_IRQHandler(void)
{
	if((ADC1->SR & SR_EOC) != 0)
	{
		/*clear EOC*/
		ADC1->SR &= ~SR_EOC;

		/*Do Something...*/
		ADC_callback();
	}
}
