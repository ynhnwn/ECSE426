//////////////////////////////////////////
//	File Name					: GPIO_pins.h			//
//	Description				: program header	//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

#ifndef _GPIO_PINS_H
#define _GPIO_PINS_H

// DEFINES
#define LED_PORT GPIOD
#define PORT_B_DISP GPIOB
#define PORT_E_DISP GPIOE

#define GREEN_PIN GPIO_PIN_12  	// Pin D12 is connected to the onboard green LED
#define ORANGE_PIN GPIO_PIN_13	// Pin D13 is connected to the onboard orange LED
#define RED_PIN GPIO_PIN_14			// Pin D14 is connected to the onboard red LED
#define BLUE_PIN GPIO_PIN_15		// Pin D15 is connected to the onboard blue LED

#define LED_PORT_CLK_EN __HAL_RCC_GPIOD_CLK_ENABLE();
#define SEGMENT_CLOCK_B_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE();
#define SEGMENT_CLOCK_E_ENABLE __HAL_RCC_GPIOE_CLK_ENABLE();

//#define SEGMENT_CLOCK_D_ENABLE __HAL_RCC_GPIOD_CLK_ENABLE();
//#define SEGMENT_CLOCK_C_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE();

//#define Output_keypad = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//#define Input_keypad = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11

// PROTOTYPES
void gpio_led_init(void);
void init_segment_disp(void);
void init_segment_segments(void);
void display(int, int);
void led_number(char, int);
void led_char(char, int);

#endif /*_GPIO_PINS_H*/
