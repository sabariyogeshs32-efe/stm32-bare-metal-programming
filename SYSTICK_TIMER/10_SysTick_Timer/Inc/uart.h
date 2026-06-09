/*
 * uart.h
 *
 *  Created on: Feb 28, 2026
 *      Author: sabari yogesh
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>

void uart2_rxtx_init (void);
void uart2_tx_init (void);
char uart2_read(void);

/* Firmware modular Driver for USART2*/
#include "stm32f446xx.h"

#endif /* UART_H_ */
