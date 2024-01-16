#include "exti.h"
#include "stm32f446xx.h"

#define GPIOCENR		(1U<<2)
#define SYSCFGEN			(1U<<14)

void pc13_exti_init(void)
{
	//disable global interrupts
	//__disable_irq();

	//enable clock access to gpioc
	RCC->AHB1ENR |= GPIOCENR;

	//set pc13 as a input pin
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	//enable clock access to syscfg
	RCC->APB2ENR |= SYSCFGEN;

	//selec Port C for Exti13
	SYSCFG->EXTICR[3] |= (1U<<5);

	//unmask exti13
	EXTI->IMR |= (1U<<13);

	//select falling edge trigger
	EXTI->FTSR |= (1U<<13);

	//enable exti13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//enable global interrupts
	__enable_irq();
}
