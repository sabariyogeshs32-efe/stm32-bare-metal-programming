/*
 * i2c.h
 *
 *  Created on: Jun 2, 2026
 *      Author: sabariyogesh
 */

#ifndef I2C_H_
#define I2C_H_
#include <stdint.h>


void i2c_Init(void);
void i2c_Read(uint8_t slave_addr,uint8_t mem_addr,char *data);
void i2c_Burst_Read(uint8_t slave_addr,uint8_t mem_addr,char *data,uint32_t n);
void i2c_Burst_Write(uint8_t slave_addr,uint8_t mem_addr,char *data,uint32_t n);
void Delay_ms(volatile uint32_t ms);




#endif /* I2C_H_ */
