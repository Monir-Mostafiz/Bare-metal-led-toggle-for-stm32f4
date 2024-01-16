#include "stm32f446xx.h"
#include "adc.h"

#define ADC1ENR			(1U<<8)
#define GPIOAENR		(1U<<0)

#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	(1U<<20)
#define CR2_ADCON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC			(1U<<1)


void pa1_adc_init(void)
{
	//enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAENR;
	//set the mode of PA1 to analog
	GPIOA->MODER |=(1U<<2);
	GPIOA->MODER |=(1U<<3);

	//cofigure the adc module
	//enable clock access to adc
	RCC->APB2ENR |= ADC1ENR;
	//confugure adc perameters
	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	//enable adc module
	ADC1->CR2 |= CR2_ADCON;
}

void start_conversion(void)
{
	//start the adc conversion
	ADC1->CR2 |= CR2_SWSTART;

}

uint32_t adc_read(void)
{
	//wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC)){}
	//read converted result
	return (ADC1->DR);
}








