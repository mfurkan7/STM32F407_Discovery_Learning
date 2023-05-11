#include "uart.h"
#define GPIOAEN		(1U<<0)
#define USART2EN	(1U<<17)

#define CR1_TE		(1U<<3)
#define CR1_UE		(1U<<13)
#define SR_TXE		(1U<<7)

#define SYS_FREQ	16000000
#define baudRate	115200

static void set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t baudrate);
static uint16_t calc_baudrate(uint32_t PeriphClk, uint32_t baudrate);

void uart_write(int ch);

int __io_putchar(int ch){
	uart_write(ch);
	return ch;
}


void uart_write(int ch){
	while(!(USART2->SR & SR_TXE)){}
	USART2->DR = (ch & 0xFF);
}

void uart_init(void){
	//AHB1 clock enable
	RCC->AHB1ENR |= GPIOAEN;

	//Set GPIO mode
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	//Set GPIO alternate function
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//APB1 clock enable
	RCC->APB1ENR |= USART2EN;

	//Set baud rate
	set_baudrate(USART2,SYS_FREQ,baudRate);

	//Enable USART (UE)
	USART2->CR1 = CR1_UE;

	//Enable TX (TE)
	USART2->CR1 |= CR1_TE;

	//Set word length
	USART2->CR1 &=~(1U<<12);

	//Set stop bit number
	USART2->CR2 &=~(1U<<12);
	USART2->CR2 &=~(1U<<13);
}

static void set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t baudrate){
	USARTx->BRR = calc_baudrate(PeriphClk,baudrate);
}

static uint16_t calc_baudrate(uint32_t PeriphClk, uint32_t baudrate){
	return ((PeriphClk + (baudrate/2U))/baudrate);

}
