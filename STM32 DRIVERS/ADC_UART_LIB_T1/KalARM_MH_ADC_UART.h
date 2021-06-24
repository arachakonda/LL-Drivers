#ifndef KalARM_MH_ADC_UART
#define KalARM_MH_ADC_UART

#include "stm32f10x.h"
#include <string.h>




void usart1_config(void);
void usart1_dma_tx(char string[]);

void usart1_enable_tx(void);

void adc_init(uint16_t *adc_val);

void delay_ms(int ms);




#endif
