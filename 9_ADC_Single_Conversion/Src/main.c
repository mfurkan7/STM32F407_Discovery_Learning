#include <stdio.h>
#include <stdint.h>
#include "stm32f407xx.h"
#include "uart.h"
#include "adc.h"

u_int32_t adc_value;

int main(void){
	uart2_rxtx_init();
	adc3_init();

	while(1){
		adc_start_conversion();
		adc_value=adc_read();
		printf("Read ADC Value: %d\n\r",(int)adc_value);
	}
}
