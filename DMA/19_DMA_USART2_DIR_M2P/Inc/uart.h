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
void uart2_write(int ch);
void dma_usart2_dir_m2p_init(uint32_t src,uint32_t dst,uint32_t len);

#define SR_RXNE			(1U<<5)
#define SR_TXE			(1U<<7)
#define TXEIE			(1U<<7)
#define DMA_TCIF6 		(1U<<21)
#define DMA_HTIF6 		(1U<<20)
/* Firmware modular Driver for USART2*/
#include "stm32f446xx.h"

#endif /* UART_H_ */
