//Where is the LED connected? I choose the orange LED to control.
//Port:D
//Pin:13
#include <stdint.h>
#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET			(0x0C00UL)
#define GPIOD_BASE				(AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIODEN 				(1U<<3) // Set bit 3 to 1 to enable the GPIO port D clock ENABLE

#define PIN13 					(1U<<13)
#define ORANGE_LED_PIN			PIN13

#define __IO volatile

typedef struct{
	volatile uint32_t MODER; // Address offset 0x04
	volatile uint32_t DUMMY[4]; // Address offset increases 4bytes = 32bits with per array
	volatile uint32_t ODR;
}GPIO_TypeDef;

typedef struct{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR; // Address offset 0x30
}RCC_TypeDef;

#define RCC 					((RCC_TypeDef*)RCC_BASE)
#define GPIOD					((GPIO_TypeDef*)GPIOD_BASE)


int main(void){
	/*1. ENABLE THE CLOCK ACCESS TO GPIOD*/
	RCC->AHB1ENR |= GPIODEN;
	/*2. SET PD13 AS OUTPUT*/
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);
	while(1){
		/*3F. EXPERIMENT: TOGGLE THE LED*/
		GPIOD->ODR ^= ORANGE_LED_PIN;
		for(int i=0;i<100000;i++){
			//I've added delay with this for loop.
		}

	}
}
