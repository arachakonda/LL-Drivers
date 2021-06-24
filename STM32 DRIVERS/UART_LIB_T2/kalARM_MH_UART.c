#include "KalARM_MH_UART.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

void delay_ms(int ms){

	msTicks=0;
	while (msTicks<ms);

}

void SysTick_Handler(void){
	
	msTicks++;

}

