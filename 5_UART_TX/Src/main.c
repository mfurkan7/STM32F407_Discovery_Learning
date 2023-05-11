#include "stm32f407xx.h"
#include <stdint.h>

/*USED DISCOVERY BOARD PIN:PD5 AS TX(TRANSMITTER)*/

#define UART2EN				(1U<<17)
#define GPIODEN 			(1U<<3)

#define CR1_TE				(1U<<3)
#define CR1_UE				(1U<<13)
#define SR_TXE				(1U<<7)

#define SYS_FREQ 			16000000
#define APB1_CLK 			SYS_FREQ
#define UART_BAUDRATE		115200

static void UART_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_UART_baudrate(uint32_t PeriphClk, uint32_t BaudRate);
void UART2_TX_Init(void);
void UART2_write(int ch);

int main(void){
	UART2_TX_Init();
	while(1){
		UART2_write('F');
		for(int i=0;i<1000000;i++){}
	}
}

void UART2_TX_Init(void){
	/*Enable clock access to GPIOD*/
	RCC->AHB1ENR |= GPIODEN;
	/*PD5 -> TX
	 *PD6 -> RX*/
	/*Configure Pin D5 Function Mode to Alternate Function Mode*/
	GPIOD->MODER &= ~(1U<<10);
	GPIOD->MODER |= (1U<<11);

	/*Configure UART_TX Alternate Function Type to UART_TX AF7 */
	GPIOD->AFR[0] |= (1U<<20);
	GPIOD->AFR[0] |= (1U<<21);
	GPIOD->AFR[0] |= (1U<<22);
	GPIOD->AFR[0] &=~(1U<<23);

	/*Configure the UART Module*/
	RCC->APB1ENR |= UART2EN;

	/*Configure the Baud rate*/
	UART_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*Configure the transfer direction*/
	USART2->CR1 = CR1_TE; // To clean all the information in UART, we don't put or(|) operator
	USART2->CR1|= CR1_UE; // Enable the USART
	//Set word length
	USART2->CR1 &=~(1U<<12);

	//Configure Stop Bit
	USART2->CR2 &=~(1U<<12);
	USART2->CR2 |= (1U<<13);
}

void UART2_write(int ch){
	while(!(USART2->SR & SR_TXE)){} // We are being sure that the transmit data register is empty.
	USART2->DR = (ch & 0xFF);

}
static void UART_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_UART_baudrate(PeriphClk,BaudRate);
}
static uint16_t compute_UART_baudrate(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate / 2U))/BaudRate);
}
