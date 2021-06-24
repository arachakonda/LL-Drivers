#include "stm32f10x.h"
#include "KalARM_MH_ADC_UART.h"
#include <stdio.h>


uint16_t adc_val[1];
uint16_t time[1];
	

int main(){
	//configure system clock or timer
	SysTick_Config(SystemCoreClock/1000);
	
	//always initialize adc1 first because of its top priority
	adc_init(adc_val); 
	//connfigure usart1
	usart1_config();
	//initialize sample string
	char string[]="KalARM";
	
	
	//enable string transfer
	usart1_enable_tx();

	


	
	while(1){	
		
			//type casting 
			sprintf(string, "%d\r", *adc_val);
		
			//transmit
			usart1_dma_tx(string);
			
			DMA1_Channel4->CCR |= DMA_CCR4_EN;
			while((DMA1->ISR& DMA_ISR_TCIF4)==0);
			DMA1->IFCR = DMA_IFCR_CTCIF4;
			DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
		
		
			
		
		
			delay_ms(1);
			


			
		
	
	}
	


}



