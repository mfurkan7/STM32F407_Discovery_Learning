#include "stm32f407xx.h"

#define TIM2EN		(1U<<0)
#define TIM4EN		(1U<<2)
#define TIM_CEN		(1U<<0)
#define TIM4_OC1M 	(1U<<4|1U<<5)
#define TIM4_CC1E	(1U<<0)

#define RCC_GPIODEN	(1U<<3)
#define PIN13		(1U<<13)
#define ORANGE_LED	PIN13

void tim2_1Hz_init(void){
	/*Enable the Timer clock*/
	RCC->APB1ENR |= TIM2EN;
	/*Set Prescaler PSC*/
	TIM2->PSC = 16000 - 1;
	/*Set the counter value*/
	TIM2->CNT = 0; // As the default counter is upcounter
	/*Set Auto-Reload Register ARR*/
	TIM2->ARR = 1000 - 1;
	/*Enable the Timer 2 counter*/
	TIM2->CR1 |= TIM_CEN;
}

void tim4_PD13_CCM_init(void){
	//LED GPIOD Clock Configuration
	RCC->AHB1ENR |= RCC_GPIODEN;
	//Set the PD12 as OUTPUT
	GPIOD->MODER &=~(1U<<24);
	GPIOD->MODER |=	(1U<<25);
	/*AF2 Settings*/
	GPIOD->AFR[1] |= (1U<<17);
	/*Enable the Timer clock*/
	RCC->APB1ENR |= TIM4EN;
	/*Set Prescaler PSC*/
	TIM4->PSC = 16000 - 1;
	/*Set the counter value*/
	TIM4->CNT = 0; // As the default counter is upcounter
	/*Set Auto-Reload Register ARR*/
	TIM4->ARR = 1000 - 1;
	/*Enable the Timer 2 counter*/
	TIM4->CR1 |= TIM_CEN;
	/*Set the CC mode as Toggle mode*/
	TIM4->CCMR1 |= TIM4_OC1M;
	/*Enable the CC output register*/
	TIM4->CCER |= TIM4_CC1E;
}
