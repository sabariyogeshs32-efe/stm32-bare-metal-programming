/*
 * adc.c
 *
 *  Created on: May 23, 2026
 *      Author: sabariyogesh
 */
#include "stm32f446xx.h"
#include "adc.h"
#define ADC1_EN		(1U<<8)
#define GPIOAEN		(1U<<0)
#define ADC_CH1		(1U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)



void adc1_init(void)
{

	/*Start Configuring the ADC Pin...*/

	/*1.Enable Clk to GPIOA since we use adc pin as pa1*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Make the pa1 as analog input*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);




	/*Start Configuring the ADC Module...*/

	/*1.Enable Clk to ADC1 Module*/
	RCC->APB2ENR |= ADC1_EN;

	/*Convertion Sequence Start*/
	/*2.Set Convertion Sequence Length and set the order*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->SQR3 = ADC_CH1;

	/*3.Enable the ADC Module  */
	ADC1->CR2 |= CR2_ADON;


}

void start_of_convertion(void)
{
	/*Enable SOC (SWSTART) bit in CR2*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t read_value(void)
{
	/*Check whether the Convertion ends...*/
	while(!(ADC1->SR & SR_EOC))
	{

	}
	/*return the converted_digital value...*/
	return ADC1->DR;
}
