//Where is the LED connected? I choose the orange LED to control.
//Port:D
//Pin:13

#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOD_OFFSET			(0x0C00UL)
#define GPIOD_BASE				(AHB1PERIPH_BASE + GPIOD_OFFSET)
#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET      	(0x30UL)
#define RCC_AHB1EN_R 			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x0000UL)
#define GPIOD_MODE_R			(*(volatile unsigned int *)(GPIOD_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET 			(0x14UL)
#define GPIOD_OD_R				(*(volatile unsigned int *)(GPIOD_BASE + OD_R_OFFSET))

#define GPIODEN 				(1U<<3) // Set bit 3 to 1 to enable the GPIO port D clock ENABLE

#define PIN13 					(1U<<13)
#define ORANGE_LED_PIN			PIN13


/*(1U<<26) // Set bit 26 to 1
 * &=~(1U<<27)// Set bit 27 to 0*/

int main(void){
	/*1. ENABLE THE CLOCK ACCESS TO GPIOD*/
	RCC_AHB1EN_R |= GPIODEN;
	/*2. SET PD13 AS OUTPUT*/
	GPIOD_MODE_R |= (1U<<26);
	GPIOD_MODE_R &=~(1U<<27);
	while(1){
		/*3. SET ORANGE_LED_PIN HIGH*/
		//GPIOD_OD_R |= ORANGE_LED_PIN;

		/*4. EXPERIMENT: TOGGLE THE LED*/
		GPIOD_OD_R ^= ORANGE_LED_PIN;
		for(int i=0;i<1000000;i++){
			//I've added delay with this for loop.
		}

	}
}
