#ifndef KalARM_MH_UART
#define KalARM_MH_UART

#include "stm32f10x.h"
#include <string.h>



void usart1_config(void);
void usart1_dma_tx(char string[]);

void usart1_enable_tx(void);
void delay_ms(int ms);


#endif

