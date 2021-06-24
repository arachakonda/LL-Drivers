#include "stm32f10x.h"
#include "KalARM_MH_UART.h"


int main(){
	
	SysTick_Config(SystemCoreClock/1000);
	usart1_config();
	
	char a[]="coma";
	
	usart1_dma_tx(a);
	
	usart1_enable_tx();
	
	while(1){
		
			DMA1_Channel4->CCR |= DMA_CCR4_EN;
			while((DMA1->ISR& DMA_ISR_TCIF4)==0);
			DMA1->IFCR = DMA_IFCR_CTCIF4;
			DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
			delay_ms(1000);
		
	
	}

	


}

