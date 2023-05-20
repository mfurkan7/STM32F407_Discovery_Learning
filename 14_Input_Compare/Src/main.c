/*We'll connect PD12 pint to PB4 pin in this project.*/
/*When PD12 has the rising edge signal, PB4 will be triggered.*/
#include <stdio.h>
#include <stdint.h>
#include "stm32f407xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "time.h"

int timestamp = 0;

int main(void){
	tim4_PD12_CCM_init();
	tim3_PB4_CCM_init();
	while(1){
		while(!(TIM3->SR & TIM3_SR_CC1IF)){}
		timestamp = TIM3->CCR1;
	}
}
