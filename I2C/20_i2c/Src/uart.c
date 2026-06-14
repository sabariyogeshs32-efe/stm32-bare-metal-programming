/*
 * uart.c
 *
 *  Created on: Feb 28, 2026
 *      Author: sabariyogesh
 */
#include "uart.h"
#define GPIOAEN 	(1U<<0)
#define USART2EN	(1U<<17)
#define SYS_FREQ		16000000U
#define APB1_clk		(SYS_FREQ)
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE			(1U<<13)
#define USART_BR		115200U
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)
#define RXNEIE			(1U<<5)
#define TXEIE			(1U<<7)


/*FOR DMA PURPOSE*/
#define DMA1EN				(1U<<21)
#define DMA_Sx_EN			(1U<<0)
#define DMA_CH4				(1U<<27)
#define DMA_DIR_MEM_PERIPH	(1U<<6)
#define DMA_MINC			(1U<<10)
#define DMA_TCIE			(1U<<4)
#define DMA_HTIE			(1U<<3)
#define UART_CR3_DMAT		(1U<<7)


void uart2_set_Baud_Rate(USART_TypeDef *USARTx, uint32_t periph_clk,uint32_t Baud_Rate);
static uint16_t USART_bd(uint32_t periph_clk, uint32_t Baud_Rate);
void uart2_write(int ch);
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_rxtx_init (void)
{

/* 1.Enable Clk to USART2 in APB1 BUS */
	RCC->APB1ENR |= USART2EN;

/* 2.Enable Clk for PA bcz it is for USART2_TX */
	RCC->AHB1ENR |=GPIOAEN;

/* 3.In GPIOA make the mode of the port as AFM in MODER register AFRL make for AF7 IN this register for PA2 */
/* set PA2 for USART TX mode */
	GPIOA->MODER |= (0x2<<4);

	GPIOA->AFR[0] |= (0x7<<8);
/* set PA3 for USART RX mode */
	GPIOA->MODER |= (0x2<<6);

	GPIOA->AFR[0] |= (0x7<<12);


/* 4.initialisation finished so then we have to configure all things like baud_rate,Trs_mode,Data_format:Start,stop,word_lngh */

/* 5.for Baud_rate there is an empherical value formula using peripheral_clk and baudrate */
/* 6.then for setting the Data_format we do this using Control_Register 1 and 2 */
	USART2->CR1 &= ~(1<<12); //M in CR1  	for word length
	USART2->CR2 &= ~(1<<12);
	USART2->CR2 &= ~(1<<13);	//13,12 - 00.  bcz one stop bit only ....
/* 7.then set for hardware flow control ... parity bit odd or even parity bits -> bit 9 of CR1 PS(parity selection).*/
	USART2->CR1 &= ~(1U<<9);
	uart2_set_Baud_Rate(USART2,APB1_clk,USART_BR);

	USART2->CR1 = (CR1_TE | CR1_RE);	//TE in CR1			for Transmission Enable*/

/* 8.Enable the USART in CR1 */
		USART2->CR1 |= CR1_UE;
/* 9.Finally write the data onto the data register for transmitting through UART... befor that we have to check that the data register is empty or not on while loop*/

}
//------------------------
void uart2_interrupt_handler_init(void)
{

/* 1.Enable Clk to USART2 in APB1 BUS */
	RCC->APB1ENR |= USART2EN;

/* 2.Enable Clk for PA bcz it is for USART2_TX */
	RCC->AHB1ENR |=GPIOAEN;

/* 3.In GPIOA make the mode of the port as AFM in MODER register AFRL make for AF7 IN this register for PA2 */
/* set PA2 for USART TX mode */
	GPIOA->MODER |= (0x2<<4);

	GPIOA->AFR[0] |= (0x7<<8);
/* set PA3 for USART RX mode */
	GPIOA->MODER |= (0x2<<6);

	GPIOA->AFR[0] |= (0x7<<12);


/* 4.initialisation finished so then we have to configure all things like baud_rate,Trs_mode,Data_format:Start,stop,word_lngh */

/* 5.for Baud_rate there is an empherical value formula using peripheral_clk and baudrate */
/* 6.then for setting the Data_format we do this using Control_Register 1 and 2 */
	USART2->CR1 &= ~(1<<12); //M in CR1  	for word length
	USART2->CR2 &= ~(1<<12);
	USART2->CR2 &= ~(1<<13);	//13,12 - 00.  bcz one stop bit only ....
/* 7.then set for hardware flow control ... parity bit odd or even parity bits -> bit 9 of CR1 PS(parity selection).*/
	USART2->CR1 &= ~(1U<<9);
	uart2_set_Baud_Rate(USART2,APB1_clk,USART_BR);

	USART2->CR1 = (CR1_TE | CR1_RE);	//TE in CR1			for Transmission Enable*/

/*FOR INTERRUPT HANDLER IN UART.........*/
/* 1.Enable the RXNEIE Interrupt Enable bit in CR1 */
		USART2->CR1 |= RXNEIE;

/*Enable NVIC Interrupt For UART INTERRUPT */
		NVIC_EnableIRQ(USART2_IRQn);

/* 8.Enable the USART in CR1 */
		USART2->CR1 |= CR1_UE;

/* 9.Finally write the data onto the data register for transmitting through UART... befor that we have to check that the data register is empty or not on while loop*/

}
//------------------------

void uart2_tx_init (void)
{

/* 1.Enable Clk to USART2 in APB1 BUS */
	RCC->APB1ENR |= USART2EN;

/* 2.Enable Clk for PA bcz it is for USART2_TX */
	RCC->AHB1ENR |=GPIOAEN;

/* 3.In GPIOA make the mode of the port as AFM in MODER register AFRL make for AF7 IN this register for PA2 */
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

/* 4.initialisation finished so then we have to configure all things like baud_rate,Trs_mode,Data_format:Start,stop,word_lngh */

/* 5.for Baud_rate there is an empherical value formula using peripheral_clk and baudrate */
/* 6.then for setting the Data_format we do this using Control_Register 1 and 2 */
	USART2->CR1 &= ~(1<<12); //M in CR1  	for word length
	USART2->CR2 &= ~(1<<12);
	USART2->CR2 &= ~(1<<13);	//13,12 - 00.  bcz one stop bit only ....
/* 7.then set for hardware flow control ... parity bit odd or even parity bits -> bit 9 of CR1 PS(parity selection).*/
	USART2->CR1 &= ~(1U<<9);
	uart2_set_Baud_Rate(USART2,APB1_clk,USART_BR);

	USART2->CR1 |= CR1_TE;	//TE in CR1			for Transmission Enable*/
/* 8.Enable the USART in CR1 */
		USART2->CR1 |= CR1_UE;
/* 9.Finally write the data onto the data register for transmitting through UART... befor that we have to check that the data register is empty or not on while loop*/

}



void dma_usart2_dir_m2p_init(uint32_t src,uint32_t dst,uint32_t len)
{

	/*Enable clock access to DMA1*/
	RCC->AHB1ENR |= DMA1EN;

	/*Disable DMA1 Stream6 and make sure it was disabled by checking using while...*/
	DMA1_Stream6->CR = 0;
	while(DMA1_Stream6->CR & DMA1EN){}

	/*Disable all Interrupts in DMA1 Stream6*/
	DMA1->HIFCR |= (1U<<16);
	DMA1->HIFCR |= (1U<<18);
	DMA1->HIFCR |= (1U<<19);
	DMA1->HIFCR |= (1U<<20);
	DMA1->HIFCR |= (1U<<21);

	/*Select CH4 in DMA Stream6 since usart2 is assigned to dma S6,CH4 */
	DMA1_Stream6->CR |= DMA_CH4;

	/*Select the direction for the data transfer here mem to periph */
	DMA1_Stream6->CR |= DMA_DIR_MEM_PERIPH;

	/*Disable FIFO and select direct mode*/
	DMA1_Stream6->FCR = 0;

	/*Enable Memory increment*/
	DMA1_Stream6->CR |= DMA_MINC;

	/*Enable transfer complete interrupt flag*/
	DMA1_Stream6->CR |= DMA_TCIE;
	DMA1_Stream6->CR |= DMA_HTIE;


	/*set the sourse buffer(Address)*/
	DMA1_Stream6->M0AR = src;

	/*set the destination buffer(Address)*/
	DMA1_Stream6->PAR = dst;

	/*set the length for the data transfer: Number of data items to transfer */
	DMA1_Stream6->NDTR = len;

	/*Enable the DMA1_Stream6*/
	DMA1_Stream6->CR |= DMA_Sx_EN;

	/*Enable DMA IN USART2...*/
	USART2->CR3 |= UART_CR3_DMAT;

	/*Enable the interrupt for DMA Stream6 in NVIC Interrupt Request*/
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}





char uart2_read(void)
{

	return USART2->DR;
}
void uart2_write(int ch)
{

	USART2->DR = (ch & 0xFF);
}
void uart2_set_Baud_Rate(USART_TypeDef *USARTx, uint32_t periph_clk,uint32_t Baud_Rate)
{
	USARTx->BRR =USART_bd(periph_clk,Baud_Rate);
}

static uint16_t USART_bd(uint32_t periph_clk,uint32_t Baud_Rate)
{
	return ((periph_clk + (Baud_Rate/2))/Baud_Rate);
}
