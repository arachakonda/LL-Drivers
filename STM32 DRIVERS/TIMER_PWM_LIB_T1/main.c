#include "stm32f10x.h"
//#include "Arm_TIMER.h"


int main(){
	
	
	RCC-> APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN; // enable port b and alternate function on port b
	RCC-> APB1ENR |= RCC_APB1ENR_TIM4EN; // enable timer 4 on apb1
	
	GPIOB->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1; // set the output as alternate function output push pull at 50 mhz
	GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
	
	TIM4->CCER |= TIM_CCER_CC4E;
	
	TIM4-> CR1 |= TIM_CR1_ARPE;
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	
	TIM4-> PSC = 72;
	
	TIM4-> ARR =65535;

	TIM4-> CCR4 = 32768;
	
	TIM4-> EGR |= TIM_EGR_UG;
	TIM4-> CR1 |= TIM_CR1_CEN;
	
	


}

