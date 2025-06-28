//where is the LED?
#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)

#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x0000UL)

#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x3800UL)

#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET		(0x30UL) //data-sheet: RCC_AHB1ENR
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define GPIOAEN				(1U<<0) //insert 1 at position 0
#define MODE_R_OFFSET		(0x00UL)//to configure pin5, we need modeR-5, to store data
#define OD_R_OFFSET			(0x14UL)//GPIOx_ODR ~ output data register

#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define PIN5 				(1U<<5)//GPIOx_ODR - pin 5
#define LED_PIN				PIN5

int main(void){
	//enable clock access to GPIO
	RCC_AHB1EN_R |= GPIOAEN;
	//set PA5 as output
	GPIOA_MODE_R |= (1U<<10);
	/*
	 * example to understand this better:
	   Original:     0x0FFF → 0000 1111 1111 1111  e.g initial MODE_R state
	   Mask:         0xF7FF → 1111 0111 1111 1111  ~(1U<<11)
	   Result:       0x07FF → 0000 0111 1111 1111  &=~(1U<<11)
	*/
	GPIOA_MODE_R &=~(1U<<11); //this 11th-bit to 0.

	while(1){
		// GPIOA_OD_R |= LED_PIN; //to LED on

		//fast toggling
		GPIOA_OD_R ^= LED_PIN;
		for(volatile int i=0;i<1000000;i++){}
	}
}
