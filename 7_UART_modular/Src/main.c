#include <stdio.h>
#include <stdint.h>
#include "stm32f407xx.h"
#include "uart.h"

int main(void){
	uart_init();
	while(1){
		printf("Hello All From STM32F407VGT6 Chip!\n\r");
		for(int i=0;i<100000000;i++){}
	}
}
