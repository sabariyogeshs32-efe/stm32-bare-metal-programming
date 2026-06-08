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
void uart2_interrupt_handler_init(void);
#define SR_RXNE			(1U<<5)
#define SR_TXE			(1U<<7)
void uart2_write(int ch);
#define TXEIE			(1U<<7)

/* Firmware modular Driver for USART2*/
#include "stm32f446xx.h"

#endif /* UART_H_ */
