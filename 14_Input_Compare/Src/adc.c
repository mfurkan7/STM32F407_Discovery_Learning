#include "stm32f407xx.h"
#include "adc.h"

//ADC3 PA1 Port:A | Pin:1 | APB2
#define GPIOAEN			(1U<<0)
#define APB2EN			(1U<<10)
#define ADC3_EN			(1U<<0)
#define ADC3_EOC		(1U<<1)
#define ADC3_LEN		0X00
#define ADC3_SWSTART	(1U<<30)
#define ADC3_CONT		(1U<<1)


void adc3_init(void){
	/*Enable the GPIO clock*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set GPIO Mode*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*Enable the ADC clock*/
	RCC->APB2ENR = APB2EN;

	/*Configure ADC3*/
	/*1.ADC3 On*/
	ADC3->CR2 |= ADC3_EN;
	/*2.ADC3 Sequence Settings*/
	ADC3->SQR3 |= (1U<<0);
	ADC3->SQR3 &=~(1U<<1);
	ADC3->SQR3 &=~(1U<<2);
	ADC3->SQR3 &=~(1U<<3);
	/*3.Set ADC3 Sequence Length*/
	ADC3->SQR1 = ADC3_LEN;

	/*4.Set Conversion setting*/
	ADC3->CR2 |= ADC3_CONT;
}
void adc_start_conversion(void){
	ADC3->CR2 |= ADC3_SWSTART;
}
uint32_t adc_read(void){
	while(!(ADC3->SR & ADC3_EOC)){}
	return (ADC3->DR);
}
