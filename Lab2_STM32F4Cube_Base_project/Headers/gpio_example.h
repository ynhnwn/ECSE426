//////////////////////////////////////////////////////////
//	File Name		: gpio_example.h					//
//	Description		: header file for gpio_example.c	//
//	Author			: Harsh Aurora, Team 12				//
//	Date			: Oct 1st, 2016						//
//////////////////////////////////////////////////////////

#ifndef _GPIO_EXAMPLE
#define _GPIO_EXAMPLE

#define EXAMPLE_PORT GPIOD
#define PORT_B_DISP GPIOB
#define PORT_E_DISP GPIOE
#define pin_0 GPIO_PIN_0

#define GREEN_PIN GPIO_PIN_12  		// Pin D12 is connected to the onboard green LED
#define ORANGE_PIN GPIO_PIN_13		// Pin D13 is connected to the onboard orange LED
#define RED_PIN GPIO_PIN_14			// Pin D14 is connected to the onboard red LED
#define BLUE_PIN GPIO_PIN_15		// Pin D15 is connected to the onboard blue LED

#define EXAMPLE_PORT_CLK_EN __HAL_RCC_GPIOD_CLK_ENABLE();
#define SEGMENT_CLOCK_B_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE();
#define SEGMENT_CLOCK_E_ENABLE __HAL_RCC_GPIOE_CLK_ENABLE();



void gpio_led_init(void);
void gpio_led(int);
void led_number(char, int);
void led_char(char, int);
void init_segment_disp(void);
void init_segment_segments(void);

#endif
