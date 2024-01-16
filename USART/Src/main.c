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

	uart2_rxtx_init();

	while(1)
	{
		key = uart2_read();
		if(key == '1')
		{
			GPIOA->ODR |= LED_PIN;
			printf("Led is on");
		}
		else
		{
			GPIOA->ODR &=~ LED_PIN;
			printf("Led is off");
		}
	}
}
