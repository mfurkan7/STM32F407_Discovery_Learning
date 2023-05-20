#include "stm32f407xx.h"

#define TIM2EN		(1U<<0)
#define TIM3EN		(1U<<1)
#define TIM4EN		(1U<<2)

#define TIM_CEN		(1U<<0)
#define TIM4_OC1M 	(1U<<4|1U<<5)
#define TIM4_CC1E	(1U<<0)

#define TIM3_CC1E	(1U<<0)
#define TIM3_CC1S	(1U<<0)

#define RCC_GPIODEN	(1U<<3)
#define RCC_GPIOBEN	(1U<<1)


void tim2_1Hz_init(void){
	/*Enable the Timer clock*/
	RCC->APB1ENR |= TIM2EN;
	/*Set Prescaler PSC*/
	TIM2->PSC = 16000 - 1;
	/*Set Auto-Reload Register ARR*/
	TIM2->ARR = 1000 - 1;
	/*Set the counter value*/
	TIM2->CNT = 0; // As the default counter is upcounter
	/*Enable the Timer 2 counter*/
	TIM2->CR1 |= TIM_CEN;
}

void tim4_PD12_CCM_init(void){
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
	/*Set Auto-Reload Register ARR*/
	TIM4->ARR = 1000 - 1;
	/*Set the CC mode as Toggle mode*/
	TIM4->CCMR1 |= TIM4_OC1M;
	/*Enable the CC output register*/
	TIM4->CCER |= TIM4_CC1E;
	/*Set the counter value*/
	TIM4->CNT = 0; // As the default counter is upcounter
	/*Enable the Timer 4 counter*/
	TIM4->CR1 |= TIM_CEN;
}
/*Trigger Port and Input port must have the same channel but have different timers*/
void tim3_PB4_CCM_init(void){
	//PB4 GPIOB Clock Configuration
	RCC->AHB1ENR |= RCC_GPIOBEN;
	//Set the PB4 as alternate function
	GPIOB->MODER &=~(1U<<8);
	GPIOB->MODER |=	(1U<<9);
	/*AF2 Settings*/
	GPIOB->AFR[0] |= (1U<<17);
	/*Enable the Timer clock*/
	RCC->APB1ENR |= TIM3EN;
	/*Set Prescaler PSC*/
	TIM3->PSC = 16000 - 1;
	/*Set the CC mode as Input mode*/
	TIM3->CCMR1 |= TIM3_CC1S;
	/*Enable the CC output register*/
	TIM3->CCER |= TIM3_CC1E;
	/*Enable the Timer 3 counter*/
	TIM3->CR1 |= TIM_CEN;
}
