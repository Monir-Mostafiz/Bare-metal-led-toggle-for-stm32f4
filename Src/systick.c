#include "stm32f446xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VAL		16000
#define CTRL_EABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)

void delay(int n)
{
	//configure systick
	//reload with number of clock per millisecond
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//clear systick current value register
	SysTick->VAL = 0;
	//enable systick and select onternal clock source
	SysTick->CTRL = (CTRL_EABLE | CTRL_CLKSRC);

	for(int i=0; i<n; i++)
	{
		//wait for count flag is set
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)){}
	}
	SysTick->CTRL = 0;
}
