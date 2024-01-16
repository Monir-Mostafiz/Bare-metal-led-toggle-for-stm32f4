
#include "uart.h"

#define GPIOAENR		(1U<<0)
#define USART2ENR		(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE 			(1U<<13)

#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

#define SYS_FREQ 		16000000
#define APB1CLK			SYS_FREQ

#define BAUDRATE		57600


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return(ch);

}
void uart2_rxtx_init(void)
{
	//configure uart gpio pin
	//Enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAENR;

	//set PA2 mode to alternate function mode
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &=~(1U<<4);
	//pa3
	GPIOA->MODER |= (1U<<7);
	GPIOA->MODER &=~(1U<<6);

	//set PA2 alternate function type to UART_tx
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);
	//pa3
	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);

	//Configure uart module
	//Enable clock access to uart2
	RCC->APB1ENR |= USART2ENR;

	//configure baudrate
	uart_set_baudrate(USART2,APB1CLK,BAUDRATE);

	//configure the transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);//BOTH ENABALING AT THE SAME TIME

	//enable uart module
	USART2->CR1 |= CR1_UE;
}
void uart2_tx_init(void)
{
	//configure uart gpio pin
	//Enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAENR;

	//set PA2 mode to alternate function mode
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &=~(1U<<4);

	//set PA2 alternate function type to UART_tx
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//Configure uart module
	//Enable clock access to uart2
	RCC->APB1ENR |= USART2ENR;

	//configure baudrate
	uart_set_baudrate(USART2,APB1CLK,BAUDRATE);

	//configure the transfer direction
	USART2->CR1 = CR1_TE;

	//enable uart module
	USART2->CR1 |= CR1_UE;
}


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

char uart2_read(void)
{
	while(!(USART2->SR & SR_RXNE)){}
		//write to transmit data register

		return USART2->DR;
}

void uart2_write(int ch)
{
	//make sure the transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	//write to transmit data register

	USART2->DR = (ch & 0xFF);
}
