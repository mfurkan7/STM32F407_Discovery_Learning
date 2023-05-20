#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000
#define SYSTICK_CTRL_EN 		(1U<<0)
#define SYSTICK_CTRL_CLKSOURCE	(1U<<2)
#define SYSTICK_COUNTFLAG 		(1U<<16)

void systickDelayms(int delay){
	//Set the loading value for 1ms delay
	SysTick->LOAD |= SYSTICK_LOAD_VAL;

	//Set the SysTick counter value
	SysTick->VAL = 0;

	//Enable the SysTick and Internal Clock Source
	SysTick->CTRL = (SYSTICK_CTRL_EN | SYSTICK_CTRL_CLKSOURCE);

	//Create the delay with For and While Loop
	for(int i=0;i<delay;i++){
		while(!(SysTick->CTRL & SYSTICK_COUNTFLAG)){}
	}
	SysTick->CTRL = 0x00;
}
