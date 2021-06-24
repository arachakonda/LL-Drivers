#ifndef ARM_MH_ADC
#define ARM_MH_ADC

#include "stm32f10x.h"


//port definitions
#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD
#define PORTE GPIOE
#define PORTF GPIOF
#define PORTG GPIOG

//pin modes
#define OUTPUT_MODE ((uint32_t) 0x01)
#define INPUT_MODE 	((uint32_t) 0x02)

//input mode types
#define INPUT_ANALOG 			((uint32_t) 0x00)
#define INPUT_FLOATING 		((uint32_t) 0x01)
#define INPUT_PU_PD 			((uint32_t) 0x02)

//output mode types
#define OUTPUT_GEN_PURPOSE	 		((uint32_t) 0x00)
#define OUTPUT_0D						 		((uint32_t) 0x01)
#define OUTPUT_ALT_FUNCTION	 		((uint32_t) 0x02)
#define OUTPUT_ALT_FUNCTION_OD	((uint32_t) 0x03)

#define LOW 0
#define HIGH 1

//output speed/slew rate
#define SPEED_2MHZ			((uint32_t) 0x02)
#define SPEED_10MHZ			((uint32_t) 0x01)
#define SPEED_50MHZ			((uint32_t) 0x03)

//enable peripheral clock after reset
#define RCC_CLOCK_ENABLE_APB1_ALT_FUNC (RCC->APB1ENR |=(1<<0))
#define RCC_CLOCK_ENABLE_APB2_ALT_FUNC (RCC->APB2ENR |=(1<<0))
#define RCC_CLOCK_ENABLE_PORTA		(RCC->APB2ENR |=(1<<2))
#define RCC_CLOCK_ENABLE_PORTB		(RCC->APB2ENR |=(1<<3))
#define RCC_CLOCK_ENABLE_PORTC		(RCC->APB2ENR |=(1<<4))
#define RCC_CLOCK_ENABLE_PORTD		(RCC->APB2ENR |=(1<<5))
#define RCC_CLOCK_ENABLE_PORTE		(RCC->APB2ENR |=(1<<6))
#define RCC_CLOCK_ENABLE_PORTF		(RCC->APB2ENR |=(1<<7))
#define RCC_CLOCK_ENABLE_PORTG		(RCC->APB2ENR |=(1<<8))

//cnf bits
#define CNF_POS_BIT1 (PINPOS[pinNumber]+2)// configuration bit 1
#define CNF_POS_BIT2 (PINPOS[pinNumber]+3)// configuration bit 2

//timer channel definitions
#define CH_1 1
#define CH_2 2
#define CH_3 3
#define CH_4 4










typedef struct{
	
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode;
	uint32_t mode_type;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
	
	
}GPIO_TYPE;



typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE

}edge_select;

// --function prototypes--
// pin configuration function prototype

//--GPIO Configurations--


static void gpio_config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);

static void gpio_config_pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t mode);

// ---delay functions -- 

void delay_ms(int ms);


#endif

