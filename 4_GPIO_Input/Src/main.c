#include "stm32f407xx.h"
// Push button connected to PA0 pin
//Port:A
//Pin:0
#define GPIOAEN				(1U<<0)
#define PIN0				(1U<<0)
#define PUSH_BUTTON_PIN		PIN0

#define GPIODEN 			(1U<<3)
#define PIN13				(1U<<13)
#define ORANGE_LED_PIN		PIN13


int main(void){
	/*ENABLE GPIOA PORT AND SET PIN0 AS AN INPUT*/
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);
	/*ENABLE GPIOD PORT AND SET PIN13 AS AN OUTPUT*/
	RCC->AHB1ENR |= GPIODEN;
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);

	while(1){
		/*PUSH BUTTON INPUT CHECK*/
		if(GPIOA->IDR &= PUSH_BUTTON_PIN){
			GPIOD->BSRR = ORANGE_LED_PIN; // Turns on the LED
		}
		else{
			GPIOD->BSRR =(1U<<29); 		//Turns off the LED
		}
	}
}
