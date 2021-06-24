#include "stm32f10x.h"
#include "Arm_GPIO.h"

int main(){
	
	GPIO_TYPE myGPIO;
	
	myGPIO.port = PORTA;
	myGPIO.pin = 5;
	myGPIO.mode = OUTPUT_MODE;
	myGPIO.mode_type = OUTPUT_GEN_PURPOSE;
	myGPIO.speed = SPEED_50MHZ;
	
	gpio_init(myGPIO);
	 while(1){
		gpio_toggle(myGPIO.port, myGPIO.pin);
		for(int i=0; i<5000000; i++); 
	 
	 }
	
	
	
}
