#include "Arm_TIMER.h"
#include <stdint.h>

uint32_t PINPOS[16] = {
(0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C),  //CRL register 8 pins 0 through 7, 4 bits for each pin
(0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C)}; //CRH register 8 pins 8 through 16, 4 bits for each pin

static void gpio_config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type){
	
	
	//--------------OUTPUT & INPUT MODES FOR PINS 8 to 15 -------------

	if (pinNumber >= 8){ // Go to control high register
		
		
		switch(mode_type){
			
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
				port->CRH &= ~( ( 1<<CNF_POS_BIT1 ) | ( 1<<CNF_POS_BIT2 ) );
			break;
			
			case OUTPUT_0D | INPUT_FLOATING:
				port->CRH &= ~ ( 1<<CNF_POS_BIT2 ); 
				port->CRH |= ( 1<<CNF_POS_BIT1 );
			break;
			
			case OUTPUT_ALT_FUNCTION | INPUT_PU_PD:
				port->CRH |= ( OUTPUT_ALT_FUNCTION<<CNF_POS_BIT1 );
			break;
			
			case OUTPUT_ALT_FUNCTION_OD:
				port->CRH &= ( OUTPUT_ALT_FUNCTION_OD<<CNF_POS_BIT1 );
			break;

		
		
		
		}// end of switch case
		
		
	}
	
	//--------------OUTPUT & INPUT MODES FOR PINS 0 to 7 -------------
	else{ // go to control low register

			switch(mode_type){
				case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
					port->CRL &= ~( ( 1<<CNF_POS_BIT1 ) | ( 1<<CNF_POS_BIT2 ) );
				break;
			
				case OUTPUT_0D | INPUT_FLOATING:
					port->CRL &= ~ ( 1<<CNF_POS_BIT2 ); 
					port->CRL |= ( 1<<CNF_POS_BIT1 );
				break;
			
				case OUTPUT_ALT_FUNCTION | INPUT_PU_PD:
					port->CRL |= ( OUTPUT_ALT_FUNCTION<<CNF_POS_BIT1 );
				break;
			
				case OUTPUT_ALT_FUNCTION_OD:
					port->CRL &= ( OUTPUT_ALT_FUNCTION_OD<<CNF_POS_BIT1 );
				break;
			}
	
	}

}


static void gpio_config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode){
		
	
	if (pinNumber >=8){
		if (mode == INPUT_MODE){
			port->CRH &=(1<<(PINPOS[pinNumber])| 1<<(PINPOS[pinNumber]+1) );
		}
		else{
			port->CRH |= (pinSpeed<<(PINPOS[pinNumber]));
			
		}
	
	
	}
	else{
		if(mode==INPUT_MODE)
			port->CRL &=(1<<(PINPOS[pinNumber])| 1<<(PINPOS[pinNumber]+1) );
		else
			port->CRL |= (pinSpeed<<(PINPOS[pinNumber]));
	
	}

}


void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state){

	if(state)
		port->BSRR = 1<<(pinNumber);
	else
		port->BSRR = 1<<(pinNumber+16);

}

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber){
	
	port->ODR ^= 1 << pinNumber;	

}


void gpio_init(GPIO_TYPE gpio_type){
	
	if(gpio_type.port == PORTA)
		RCC_CLOCK_ENABLE_PORTA;
	if(gpio_type.port == PORTB)
		RCC_CLOCK_ENABLE_PORTB;
	if(gpio_type.port == PORTC)
		RCC_CLOCK_ENABLE_PORTC;
	if(gpio_type.port == PORTD)
		RCC_CLOCK_ENABLE_PORTD;
	
	gpio_config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
	gpio_config_pin_speed(gpio_type.port, gpio_type.pin, gpio_type.speed, gpio_type.mode);
	
	


}


//--Interrupt Functions--

void interrupt_gpio_configure(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge){
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	if(port == PORTA){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PA;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PA;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PA;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PA;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PA;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PA;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PA;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PA;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PA;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PA;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PA;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PA;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PA;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PA;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PA;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PA;
				break;
				
			}
	
	
	}
	
	if(port == PORTB){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PB;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PB;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PB;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PB;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PB;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PB;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PB;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PB;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PB;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PB;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PB;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PB;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PB;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PB;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PB;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PB;
				break;
				
			}
	
	
	}
	if(port == PORTC){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PC;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PC;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PC;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PC;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PC;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PC;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PC;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PC;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PC;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PC;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PC;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PC;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PC;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PC;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PC;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PC;
				break;
				
			}
	
	
	}
	
	if(port == PORTD){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PD;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PD;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PD;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PD;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PD;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PD;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PD;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PD;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PD;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PD;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PD;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PD;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PD;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PD;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PD;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PD;
				break;
				
			}
	
	
	}
	if(port == PORTE){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PE;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PE;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PE;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PE;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PE;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PE;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PE;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PE;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PE;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PE;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PE;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PE;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PE;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PE;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PE;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PE;
				break;
				
			}
	
	
	}
		if(port == PORTF){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PF;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PF;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PF;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PF;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PF;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PF;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PF;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PF;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PF;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PF;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PF;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PF;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PF;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PF;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PF;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PF;
				break;
				
			}
	
	
	}
		if(port == PORTG){
		switch(pinNumber){
				case 0:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI0_PG;
				break;
				case 1:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI1_PG;
				break;
				case 2:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI2_PG;
				break;
				case 3:
					AFIO-> EXTICR[0]= AFIO_EXTICR1_EXTI3_PG;
				break;
				case 4:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI4_PG;
				break;
				case 5:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI5_PG;
				break;
				case 6:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI6_PG;
				break;
				case 7:
					AFIO-> EXTICR[1]= AFIO_EXTICR2_EXTI7_PG;
				break;
				case 8:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI8_PG;
				break;
				case 9:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI9_PG;
				break;
				case 10:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI10_PG;
				break;
				case 11:
					AFIO-> EXTICR[2]= AFIO_EXTICR3_EXTI11_PG;
				break;
				case 12:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI12_PG;
				break;
				case 13:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI13_PG;
				break;
				case 14:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI14_PG;
				break;
				case 15:
					AFIO-> EXTICR[3]= AFIO_EXTICR4_EXTI15_PG;
				break;
				
			}
	
	
	}
		
	if(edge == RISING_EDGE){
		EXTI->RTSR |= 1<<pinNumber;		
	}
	if(edge == FALLING_EDGE){
		EXTI->FTSR |= 1<<pinNumber;		
	}
	if (edge == RISING_FALLING_EDGE){
		EXTI->RTSR |= 1<<pinNumber;
		EXTI->FTSR |= 1<<pinNumber;
	}

}

void interrupt_gpio_enable(uint32_t pinNumber, IRQn_Type irqNumber){
	//Enable interrupt in EXTI
	EXTI->IMR |= 1<<pinNumber;
	
	//Enable interrupt in NVIC 
	NVIC_EnableIRQ(irqNumber);
}

void interrupt_gpio_clear(uint32_t pinNumber){
	
	EXTI->PR |= 1<<pinNumber;
	

}


//-------------- TIMER PWM FUNCTIONS --------

void timer_pwm_config(TIM_TypeDef * timer, uint32_t channel){

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



void timer_pwm_init(TIM_TypeDef * timer, uint32_t prescaler, uint32_t frequency, uint32_t channel, uint32_t duty_cycle){
	
	
	if(timer == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if(timer == TIM2 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(timer == TIM3 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if(timer == TIM4 )
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	
	
	
	timer_pwm_config(timer, channel);
	
	timer -> PSC = prescaler;
	timer -> ARR = frequency;
	
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
