#ifndef KalARM_MH_UART
#define KalARM_MH_UART

#include "stm32f10x.h"
#include <string.h>



void usart1_config(void);
void usart1_tx(char data[],uint32_t  transmit_length); 
void usart1_rx(uint32_t receive_length);

void flush_usart1(void);


#endif
