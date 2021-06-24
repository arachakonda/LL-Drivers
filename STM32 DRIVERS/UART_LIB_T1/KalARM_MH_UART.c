#include "KalARM_MH_UART.h"
#include <stdint.h>
#include <stdlib.h>


uint32_t u1_length_rx;
uint32_t u1_length_tx;



char u1_string_tx[16];
char u1_string_rx[16];

int rxi=0;
int txi=0;


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
	USART1->BRR = 0x1D4C; //for 72MHZ on APB1 bus

	//enable RXNE and TXE interrupts on USART SIDE
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;

}



void usart1_tx(char data[], uint32_t transmit_length){

	//----------|  TX enable --   UART enable
	USART1->CR1 |= USART_CR1_TE | USART_CR1_UE;
	
	u1_length_tx = transmit_length;
	
	for (int i=0;i< transmit_length; i++){
		
		u1_string_tx[i]=data[i];
		
	}
	
}






void usart1_rx(uint32_t receive_length){
	
	
	//----------|  RX enable --   UART enable
	USART1->CR1 |= USART_CR1_RE | USART_CR1_UE;
	u1_length_rx = receive_length;
	


}

void USART1_IRQHandler(void) {
	
	
		while(u1_length_rx>0){
			 //check if we are here because of RXNE interrupt
			 if (USART1->SR & USART_SR_RXNE) //if RX is not empty
			 {
					u1_string_rx[rxi]= USART1->DR; //fetch the data received
				  rxi++;
			 }
			
			 u1_length_rx --;
		 }		
	 

	 
		while(u1_length_tx>0){
			 //check if we are here because of TXEIE interrupt
			 if (USART1->SR & USART_SR_TXE) //if RX is not empty
			 {
				
					USART1->DR = u1_string_tx[txi];  //send it back out
					while (!(USART1->SR & USART_SR_TC));
				  txi++;
					

			 }
			 
			 u1_length_tx --;
			
		 }
	
		

}


void flush_usart1(void){

	u1_length_rx=0;
	u1_length_tx=0;
	
//	u1_string_rx="";
//	u1_string_tx="";
	

}




