

#include "Arm_GPIO.h"
#include <stdint.h>

uint32_t PINPOS[16] = {
(0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C),  //CRL register 8 pins 0 through 7, 4 bits for each pin
(0x00),(0x04),(0x08),(0x0C),(0x10),(0x14),(0x18),(0x1C)}; //CRH register 8 pins 8 through 16, 4 bits for each pin

static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type){
	
	
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


static void config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode){
		
	
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
	
	config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
	config_pin_speed(gpio_type.port, gpio_type.pin, gpio_type.speed, gpio_type.mode);
	
	


}
