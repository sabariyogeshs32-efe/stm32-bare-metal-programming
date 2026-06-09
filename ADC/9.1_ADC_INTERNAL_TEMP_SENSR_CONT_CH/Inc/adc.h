/*
 * adc.h
 *
 *  Created on: May 24, 2026
 *      Author: sabariyogesh
 */

#ifndef ADC_H_
#define ADC_H_
#include<stdint.h>
void adc1_int_temp_snsr_init(void);
void start_of_convertion(void);
uint32_t read_value(void);
float calculate_temperature(uint32_t adc_value);



#endif /* ADC_H_ */


