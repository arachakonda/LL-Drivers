#include "ARM_MH_TIMER_PWM.h"
#include <stdint.h>
// --delay milliseconds variable
uint32_t msTicks;


//-------------- TIMER PWM FUNCTIONS --------

void timer_pwm_config(TIM_TypeDef * timer,  uint32_t channel){
	
	
	//Counter capture enable for the channel
	switch(channel){
		case 1:
			timer -> CCER |= TIM_CCER_CC1E;
		break;
		case 2:
			timer -> CCER |= TIM_CCER_CC2E;
		break;
		case 3:
			timer -> CCER |= TIM_CCER_CC3E;
		break;
		case 4:
			timer -> CCER |= TIM_CCER_CC4E;
		break;
	}
	
	//auto-reload and preload register enable
	
	timer-> CR1=TIM_CR1_ARPE;
	
	//pwm-mode set to (higher - on) state
	
	switch(channel){
		
		case 1:
			timer ->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE;
		break;
		case 2:
			timer ->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE;
		break;
		case 3:
			timer ->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE;
		break;
		case 4:
			timer ->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
		break;
		
		
		
	
	
	}
	
	
			

}



void timer_pwm_init(TIM_TypeDef *timer, uint32_t channel, GPIO_TypeDef *port, uint32_t pinNumber,
uint32_t prescaler, uint32_t arr, uint32_t duty_cycle){
	
	
	//port enable
	if(port == PORTA)
		RCC->APB2ENR= RCC_APB2ENR_IOPAEN;
	else if(port == PORTB)
		RCC->APB2ENR= RCC_APB2ENR_IOPBEN;
	else if(port == PORTC)
		RCC->APB2ENR= RCC_APB2ENR_IOPCEN;
	else if(port == PORTD)
		RCC->APB2ENR= RCC_APB2ENR_IOPDEN;
	
	// enable peripheral clock
	RCC_CLOCK_ENABLE_APB2_ALT_FUNC;	
	
	// fix output mode and speed
	
	if(pinNumber >= 8){
		
		switch(pinNumber){
			
			case 8:
			  port->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1 | GPIO_CRH_CNF8_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF8_0);
			break;
			
			case 9:
			  port->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF9_0);
			break;
			
			case 10:
			  port->CRH |= GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF10_0);
			break;
			
			case 11:
			  port->CRH |= GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1 | GPIO_CRH_CNF11_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF11_0);
			break;
			
			case 12:
			  port->CRH |= GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1 | GPIO_CRH_CNF12_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF12_0);
			break;
			
			case 13:
			  port->CRH |= GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1 | GPIO_CRH_CNF13_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF13_0);
			break;
			
			case 14:
			  port->CRH |= GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1 | GPIO_CRH_CNF14_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF14_0);
			break;
			
			case 15:
			  port->CRH |= GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1 | GPIO_CRH_CNF15_1; // set the output as alternate function output push pull at 50 mhz
				port->CRH &= ~(GPIO_CRH_CNF15_0);
			break;
			
		
		
		}
		
		

	}
	
	else{
	
		switch(pinNumber){
			
			case 0:
			  port->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF0_0);
			break;
			
			case 1:
			  port->CRL |= GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF1_0);
			break;
			
			case 2:
			  port->CRL |= GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF2_0);
			break;
			
			case 3:
			  port->CRL |= GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_CNF3_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF3_0);
			break;
			
			case 4:
			  port->CRL |= GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1 | GPIO_CRL_CNF4_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF4_0);
			break;
			
			case 5:
			  port->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1 | GPIO_CRL_CNF5_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF5_0);
			break;
			
			case 6:
			  port->CRL |= GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF6_0);
			break;
			
			case 7:
			  port->CRL |= GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1; // set the output as alternate function output push pull at 50 mhz
				port->CRL &= ~(GPIO_CRL_CNF7_0);
			break;
			
		}
	}
	
	
	
	
	if(timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(timer == TIM2 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(timer == TIM3 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(timer == TIM4 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	
	
	timer_pwm_config(timer,channel);
	
	
	
	//set prescaler and duty cycle
	
	timer -> PSC = prescaler;
	timer -> ARR = arr;
	
	switch(channel){
		
		case 1:
			timer ->CCR1 = duty_cycle;
		break;
		case 2:
			timer ->CCR2 = duty_cycle;
		break;
		case 3:
			timer ->CCR3 = duty_cycle;
		break;
		case 4:
			timer ->CCR4 = duty_cycle;
		break;
	
	
	
	}
	
	timer->EGR |= TIM_EGR_UG;
	timer->CR1 |= TIM_CR1_CEN;
	

}


void port_reset(GPIO_TypeDef *port,uint32_t pinNumber){
	
	if(pinNumber>= 8)
		port-> CRH = 0x44444444;
	else
		port-> CRL = 0x44444444;

}

// -- delay milli seconds ---

void delay_ms(int ms){

	msTicks=0;
	while (msTicks<ms);

}

void SysTick_Handler(void){
	
	msTicks++;

}
