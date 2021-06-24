# include "stm32f10x.h"
# include "ARM_GPIO_INT.h"

//declaration of Global Variables
GPIO_TYPE led;
GPIO_TYPE interrupt;



int main(){

	
	led.pin = 13;
	led.port = PORTC;
	led.mode = OUTPUT_MODE;
	led.mode_type = OUTPUT_GEN_PURPOSE;
	led.speed= SPEED_50MHZ;
	interrupt.pin = 4;
	interrupt.port = PORTE;
	interrupt.mode = INPUT_MODE;
	interrupt.mode_type = INPUT_PU_PD;
	gpio_init(led);
	interrupt_gpio_configure(interrupt.port, interrupt.pin, RISING_EDGE);
	interrupt_gpio_enable(13, EXTI4_IRQn);

}

void EXTI4_IRQHandler(){
	interrupt_gpio_clear(4);
	
	gpio_toggle(led.port, led.pin);
	
}
