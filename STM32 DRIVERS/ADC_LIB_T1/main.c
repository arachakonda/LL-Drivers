#include "stm32f10x.h"
#include "ARM_MH_ADC.h"

uint32_t adc_val, duty_cycle;


int main(){
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	RCC->APB2ENR= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
	//channel 5 is being used in ADC1

	GPIOA-> CRL |= GPIO_CRL_CNF5_1;
	GPIOA-> CRL &= ~(GPIO_CRL_CNF5_0);
	
	ADC1->CR1 |= ADC_CR1_EOCIE;
	
	NVIC_EnableIRQ(ADC1_2_IRQn); // ADC1 and  ADC2 share the same interrupt
	
	
	// Set the first sequence to be converted in the sequence register 3 of ADC1 to the channel being used
	
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	
	// Turn on ADC for the first time and set it in continuous mode
	
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	delay_ms(1);
	
	
	// Turn on ADC for the Second time to actually turn it on
	
	ADC1->CR2 |= ADC_CR2_ADON;
	delay_ms(1);
	
	ADC1->CR2 |=ADC_CR2_CAL;
	delay_ms(2);
	


}


void ADC1_2_IRQHandler(void){
	
	if(ADC1-> SR & ADC_SR_EOC){
	
		adc_val= ADC1-> DR;
		
	}
	duty_cycle= adc_val*65535/4096;
	TIM4-> CCR4 = duty_cycle;


}