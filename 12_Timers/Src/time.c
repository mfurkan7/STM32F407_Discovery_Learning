#include "stm32f407xx.h"

#define TIM2EN		(1U<<0)
#define TIM2_CEN	(1U<<0)


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
	TIM2->CR1 |= TIM2_CEN;
}
