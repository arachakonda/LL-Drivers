#include "stm32f10x.h"
#include "KalARM_MH_UART.h"



int main(void) {
	
	
	//configure usart1 and system clock
	usart1_config();
	
	char ar[8]="aaaaaaaa";
	
	
	usart1_tx(ar,8);
	usart1_rx(8);
	
	NVIC_EnableIRQ(USART1_IRQn);
	
	

	
	


	
}


