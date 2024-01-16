#include "stm32f446xx.h"
#include "timer.h"

#define TIM2ENR		(1U<<0)
#define CR1_CEN		(1U<<0)
#define CCMR_TOGGLE	((1U<<4) | (1U<<5))
#define CCER_CC1E	(1U<<0)
#define GPIOAENR	(1U<<0)
#define TIM3ENR		(1U<<1)
#define CCER_CC1S	(1U<<0)

void tim2_1hz_init(void)
{
	//enable clock access to timer2
	RCC->APB1ENR |= TIM2ENR;
	//set prescaler value
	TIM2->PSC =  1600-1 ; // 16 000 000 / 1 600 = 10000
	//set auto reload value
	TIM2->ARR =	 10000-1 ; // 10 000 / 10 000 = 1sec (5 000-1)/10 000 = 0.5sec
	//clear the timer counter
	TIM2->CNT = 0;

	//enable the timer
	TIM2->CR1 = CR1_CEN;

}

void tim2_PA5_output_compare(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAENR;
	//Configure as a alternate function
	GPIOA->MODER |= (1U<<11);
	GPIOA->MODER &=~(1U<<10);
	//Configure alternate function mode AF1
	GPIOA->AFR[0] |= (1U<<20);
	//enable clock access to timer2
	RCC->APB1ENR |= TIM2ENR;
	//set prescaler value
	TIM2->PSC =  1600-1 ; // 16 000 000 / 1 600 = 10000
	//set auto reload value
	TIM2->ARR =	 10000-1 ; // 10 000 / 10 000 = 1sec (5 000-1)/10 000 = 0.5sec

	//set output compare toggle mode
	TIM2->CCMR1 = CCMR_TOGGLE;
	//enable tim2 ch1 in compare mode
	TIM2->CCER = CCER_CC1E;
	//clear the timer counter
	TIM2->CNT = 0;

	//enable the timer
	TIM2->CR1 = CR1_CEN;

}


void tim3_input_capture(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAENR;

	//Set PA6 as a alternate function mode
	GPIOA->MODER |=(1U<<13);
	GPIOA->MODER &=~(1U<<12);

	//Set PA6 alternate function mode to AF02
	GPIOA->AFR[0] |=(1U<<25);

	//Enable clock access to TIM3
	RCC->APB1ENR |= TIM3ENR;

	//Set prescaler value
	TIM3->PSC = 16000-1;

	//Set CH1 to INPUT capture
	TIM3->CCMR1 = CCER_CC1S;

	//set CH1 to capture at rising edge
	TIM3->CCER |= CCER_CC1E;

	//Enable TIM3
	TIM3->CR1 |= CR1_CEN;
}





