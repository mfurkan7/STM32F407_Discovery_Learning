#include "stm32f407xx.h"

#define GPIODEN 			(1U<<3)
#define PIN13				(1U<<13)
#define ORANGE_LED_PIN		PIN13


int main(void){
	RCC->AHB1ENR |= GPIODEN;
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);
	while(1){
		GPIOD->BSRR = ORANGE_LED_PIN;
		for(int i=0;i<10000000;i++){}
		GPIOD->BSRR =(1U<<29);
		for(int i=0;i<10000000;i++){}
	}
}

