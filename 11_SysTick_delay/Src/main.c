#include <stdio.h>
#include <stdint.h>
#include "stm32f407xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#define RCC_GPIODEN	(1U<<3)
#define PIN13		(1U<<13)
#define ORANGE_LED	PIN13


u_int32_t adc_value;

int main(void){
	//LED GPIOD Clock Configuration
	RCC->AHB1ENR |= RCC_GPIODEN;
	//Set the PD13 as OUTPUT
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);
	//Initialize the UART
	uart2_rxtx_init();

	while(1){
		printf("One second passed!");
		//Set the LED ON
		GPIOD->BSRR |= (1U<<13);
		systickDelayms(1000);
		//Set the LED OFF
		GPIOD->BSRR |= (1U<<29);
		systickDelayms(1000);

	}
}
