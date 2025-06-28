#include <stm32f4xx.h>

#define GPIOCEN (1U << 2)
#define GPIOAEN (1U << 0)
#define PIN5 (1U << 5)
#define PIN13 (1U << 13)
#define LED_PIN PIN5
#define BTN_PIN PIN13

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	// set PA5 as output pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	// // set PC13 as input pin(uses GPIOC)
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	while (1)
	{
		if (GPIOA->IDR & BTN_PIN)
		{
			GPIOA->BSRR |= LED_PIN;
			// GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->BSRR |= (1U << 21);
			// GPIOA->ODR &= ~(1U << 5);
		}
	}
}