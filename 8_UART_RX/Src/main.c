#include <stdio.h>
#include <stdint.h>
#include "stm32f407xx.h"
#include "uart.h"

#define GPIODEN			(1U<<3)
#define PIN13			(1U<<13)
#define ORANGE_LED_PIN	PIN13

char data;

int main(void){

	RCC->AHB1ENR |= GPIODEN;
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);
	uart2_rxtx_init();

	while(1){
		data=uart2_read();
		if(data == '1'){
			GPIOD->ODR |= ORANGE_LED_PIN;
		}
		else{
			GPIOD->ODR &=~ORANGE_LED_PIN;
		}
	}
}
