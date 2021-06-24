#include "KalARM_MH_ADC_UART.h"
#include <stdint.h>
// --delay milliseconds variable

uint32_t msTicks;




void usart1_config(void){
	//-----------------------| UART CODE |------------------------------------------
	//USART1 / GPIOA/(GPIOB and Alternate Function) clock enable
	//RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN; 
	// donot forget to initialize alternate function clock in the apb2 register
	

	//remaping if needed
	AFIO->MAPR |= AFIO_MAPR_USART1_REMAP ; //remap RX TX to PB7 PB6

	// pin configurations: PA9/PB6- TX is set to ALternate-push-pull and 50MHz
	// GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
	// GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
	
	GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1;
	GPIOB->CRL &= ~(GPIO_CRL_CNF6_0);
	

	/*
		* PIN PA10/PB7 is the RX pin and it has to be set to input and FLOATING
		* this is the rest value of the pin so we really dont have to do anything to it.
		*
		* */

	//USART DIV value
	

	//enable RXNE and TXE interrupts on USART SIDE
  //USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
	

	
	
	
	

}

void usart1_dma_tx(char string[]){
	//DMA operations
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	USART1->CR3 |= USART_CR3_DMAT;
	
	DMA1_Channel4->CNDTR = strlen(string);
	DMA1_Channel4->CCR |= DMA_CCR4_MINC | DMA_CCR4_DIR | DMA_CCR4_TCIE | DMA_CCR4_CIRC;
	
	
	
	DMA1_Channel4->CPAR = (uint32_t)&USART1->DR;
	
	DMA1_Channel4->CMAR = (uint32_t)string;
	
	
	
}

void usart1_enable_tx(void){

	USART1->BRR = 0x1D4C; 
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_UE;


}


//-- adc functions--

void adc_init(uint16_t *adc_val){
	
		//change prescaler for ADC to not exceed 14Mhz
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	//RCC Clocks for ADC and ALT function	
	RCC->APB2ENR= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
	//enable DMA1 on the AHB register	
	RCC->AHBENR= RCC_AHBENR_DMA1EN;
	//channel 10 is being used in ADC1 which is pin 0 on port C
	GPIOC-> CRL |= GPIO_CRL_CNF0_1;
	GPIOC-> CRL &= ~(GPIO_CRL_CNF0_0);
	//set sampling rate in the samping rate register
	ADC1->SMPR1 |= ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_0;
	// Set the first sequence to be converted in the sequence register 3 of ADC1 to the channel being used
	ADC1->SQR3 |= ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_3;
	
	//ADC DMA Enable and Scan
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_DMA;
	*adc_val=0;
	//DMA Settings
	DMA1_Channel1 -> CPAR = (uint32_t)(&(ADC1->DR));
	DMA1_Channel1 -> CMAR = (uint32_t)(adc_val); // address of the receiver buffer
	DMA1_Channel1 -> CNDTR = 1; // number of data to transfer
	DMA1_Channel1 -> CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
	
	
	// Turn on ADC for the first time and set it in continuous mode
	
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	delay_ms(1);
	
	
	// Turn on ADC for the Second time to actually turn it on
	
	ADC1->CR2 |= ADC_CR2_ADON;
	delay_ms(1);
	
	ADC1->CR2 |=ADC_CR2_CAL;
	delay_ms(2);


}


//---delay functions --
void delay_ms(int ms){

	msTicks=0;
	while (msTicks<ms);

}

void SysTick_Handler(void){
	
	msTicks++;

}


