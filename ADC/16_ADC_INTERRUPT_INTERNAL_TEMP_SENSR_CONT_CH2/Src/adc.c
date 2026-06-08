/*
 * adc.c
 *
 *  Created on: May 23, 2026
 *      Author: sabariyogesh
 */
#include "stm32f446xx.h"
#include "adc.h"
//-------CALLI---------///////
#define TS_CAL1_ADDR  ((uint16_t*)0x1FFF7A2C)
#define TS_CAL2_ADDR  ((uint16_t*)0x1FFF7A2E)

#define TS_CAL1_TEMP  30.0f
#define TS_CAL2_TEMP  110.0f

//-------CALLI---------///////
#define ADC1_EN			(1U<<8)
#define GPIOAEN			(1U<<0)
#define ADC_CH18		(18U<<0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define CCR_TSVREFE		(1U<<23)
#define VBATE			(1U<<22)
#define SMP18_480cycles	(7U<<24)
#define CCR_PCLK2_BY_4	(1U<<16)
#define CR2_CONT		(1U<<1)
#define CR1_EOCIE		(1U<<5)



void adc1_int_temp_snsr_init(void)
{

//	/*Start Configuring the ADC Pin...*/
//
//	/*1.Enable Clk to GPIOA since we use adc pin as pa1*/
//	RCC->AHB1ENR |= GPIOAEN;
//
//	/*2.Make the pa1 as analog input*/
//	GPIOA->MODER |= (1U<<2);
//	GPIOA->MODER |= (1U<<3);

	/*1.Enable Clk to ADC1 Module*/
		RCC->APB2ENR |= ADC1_EN;

	/*We need to enable the internal Temperature sensor in CCR Register...*/
	ADC->CCR |= CCR_TSVREFE;
	/*While enabling the internal temperature sensor we must need to turn of the VBATE because if both are on the highest priority is VBATE and int_temp_snsr is ignored*/
	ADC->CCR &= ~VBATE;

	/*Adding some delay for some stabilizing...*/
	//for(int i=0;i<10000;i++);


	/*prescale the clk to slow down ADC to get precise reading...*/
	//ADC->CCR |= CCR_PCLK2_BY_4;

	/*Enabling the continous mode in CR2 Regsiter*/
	ADC1->CR2 |= CR2_CONT;

	/*Enable NVIC for ADC*/
	NVIC_EnableIRQ(ADC_IRQn);

	/*Start Configuring the ADC Module...*/



	/*Convertion Sequence Start*/
	/*2.Set Convertion Sequence Length and set the order*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->SQR3 = ADC_CH18;
	ADC1->CR1 |= CR1_EOCIE;


	/*Set the Sampling time to maximum value as much as possible since the int_temp_sensor is so weak more sampling time req to good reading ... max is 480cycles/sec so use that in SMPR1 Register for CH_18*/
//	ADC1->SMPR1 = SMP18_480cycles;
	/*3.Enable the ADC Module  */
	ADC1->CR2 |= CR2_ADON;


}

void start_of_convertion(void)
{
	/*Enable SOC (SWSTART) bit in CR2*/
	ADC1->CR2 |= CR2_SWSTART;
}


float calculate_temperature(uint32_t adc_value)
{
    uint16_t ts_cal1 = *TS_CAL1_ADDR;
    uint16_t ts_cal2 = *TS_CAL2_ADDR;

    float temperature;

    temperature =
            ((float)(adc_value - ts_cal1) *
            (TS_CAL2_TEMP - TS_CAL1_TEMP))
            /
            (float)(ts_cal2 - ts_cal1)
            +
            TS_CAL1_TEMP;

    return temperature;
}
