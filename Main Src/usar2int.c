#include <stdio.h>
#include "stm32f446xx.h"
#include <stdint.h>
#include "uart.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)
#define LED_PIN			PIN5

char key;

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_rx_interrupt_init();

	while(1)
	{



	}
}


void USART2_IRQHandler(void)
{
	//check if RXNE is set
	if(USART2->SR & SR_RXNE)
	{
		key = USART2->DR;

		if(key == '1')
				{
					GPIOA->ODR |= LED_PIN;
				}
				else
				{
					GPIOA->ODR &=~ LED_PIN;
				}
	}
}
