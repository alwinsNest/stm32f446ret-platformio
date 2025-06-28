//struct method of accessing registers.
#include <stdint.h>
#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)
#define GPIOAEN				(1U<<0) //insert 1 at position 0
#define PIN5 				(1U<<5)//GPIOx_ODR - pin 5
#define LED_PIN				PIN5
#define __IO 				volatile	

typedef struct
{//ref manual - 6.3 RCC registers
	volatile uint32_t DUMMY[12];//skips first 12 register offsets.
	volatile uint32_t AHB1ENR;
} RCC_TypeDef;

typedef struct 
{//here each member occupies 4 bytes (32 bit/8) so all are offset by 4
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4]; 
	volatile uint32_t ODR;
} GPIO_TypeDef;

#define RCC 	((RCC_TypeDef*)RCC_BASE)
#define GPIO	((GPIO_TypeDef*)GPIOA_BASE)

int main(void){
	//enable clock access to GPIO
	RCC->AHB1ENR |= GPIOAEN;
	//set PA5 as output setting 10,11 bit values.
	GPIO->MODER |= (1U<<10);
	/*
	 * example to understand this better:
	   Original:     0x0FFF → 0000 1111 1111 1111  e.g initial MODE_R state
	   Mask:         0xF7FF → 1111 0111 1111 1111  ~(1U<<11)
	   Result:       0x07FF → 0000 0111 1111 1111  &=~(1U<<11)
	*/
	GPIO->MODER &=~(1U<<11); //this 11th-bit to 0.

	while(1){
		// GPIOA_OD_R |= LED_PIN; //to LED on

		//fast toggling
		GPIO->ODR ^= LED_PIN;
		for(volatile int i=0;i<1000000;i++){}
	}
}
