//////////////////////////////////////////
//	File Name					: GPIO_pins.c			//
//	Description				: program entry		//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "sysclk_config.h"
//#include "lis3dsh.h"
//#include "arm_math.h"
#include "GPIO_pins.h"
 
// INITIALISE LED SEGMENTS
void gpio_led_init(void) 
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	LED_PORT_CLK_EN; 									
	
	GPIO_InitDef.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8; 	
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitDef);
	HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_8, GPIO_PIN_RESET);
}

// INITIALISE 7-SEGMENTS DISPLAYS
void init_segment_disp(void)
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	SEGMENT_CLOCK_B_ENABLE;
	
	// INDIVIDUAL DISPLAY MAPPED TO RGB LEDS (PIN 12-15)
	GPIO_InitDef.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11; 	
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(PORT_B_DISP, &GPIO_InitDef);
	HAL_GPIO_WritePin(PORT_B_DISP, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11, GPIO_PIN_RESET);
}

// INITIALIZE THE DISPLAY DIGITS
void init_segment_segments(void)
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	SEGMENT_CLOCK_E_ENABLE;
	
	// INDIVIDUAL DISPLAY MAPPED TO RGB LEDS (PIN 12-15)
	GPIO_InitDef.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12; 	
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(PORT_E_DISP, &GPIO_InitDef);
	HAL_GPIO_WritePin(PORT_E_DISP, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12, GPIO_PIN_RESET);
}

// DISPLAY SWITCH FUNCTION
void display(int value, int display) {
	switch (display) {
		case 0:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		
			// CHOOSING WHAT TO DSIPLAY
			if(value >= 0)
			{
				led_number(((value%1000)-(value%100))/100, 0);
			} 
			else if(value == -1)
			{
				
			}
								
			break;
	
		case 1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);

			// CHOOSING WHAT TO DSIPLAY	
			if(value >= 0)
			{
				led_number(((value%100)-(value%10))/10, 0);
			}
			else if(value == -1)
			{
				
			}
			
			break;

		case 2:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

			// CHOOSING WHAT TO DSIPLAY
			if(value >= 0)
			{
				led_number((value%10), 0);
			}
			else if(value == -1)
			{
				
			}
		
			break;

		case 3:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			
			// CHOOSING WHAT TO DSIPLAY
			if(value >= 0)
			{
				led_char('p', 0);
			}
			else if(value == -1)
			{
				
			}
		
			break;

		case -1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		default:
			break;
	}
}

/*
 *Brief:	Toggles the value of the desired pin
 *Params:	None
 *Return:	None
 */

/* 7-SEGMENTS DISPLAY TO STM32F4XX PIN REFERENCE
 *
 *	PIN 14 = PIN D 11			// A
 *	PIN 16 = PIN D 10			// B
 *	PIN 13 = PIN D  9			// C
 *	PIN  3 = PIN D  8			// D
 *	PIN  5 = PIN B 15			// E
 *	PIN 11 = PIN B 14			// F
 *	PIN 15 = PIN B 13 		// G
 *	PIN  7 = PIN B 12			// LOWER DOT
 *	PIN 10 = PIN B 11			// UPPER DOT
*/

// SWITCH STATEMENT FOR CHOSING WHAT NUMBER TO DISPLAY
void led_number(char number, int dot){
	switch(number){
		
		// DISPLAY NUMBER 0
		case 0:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
			
		// DISPLAY NUMBER 1
		case 1:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		// DISPLAY NUMBER 2
		case 2:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 3
		case 3:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		// DISPLAY NUMBER 4
		case 4:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 5
		case 5:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 6
		case 6:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 7
		case 7:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
		  break;
		
		// DISPLAY NUMBER 8
		case 8:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 9
		case 9:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			
		default:
			break;
	}
	
	// DISPLAY DOT
	if(dot==1){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);					// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	} else if(dot==2){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);					// UPPER DOT
	}	else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	}
}

// SWITCH STATEMENT FOR CHOSING WHAT CHARACTER TO DISPLAY
void led_char(char number, int dot){
	switch(number){
		
		// DISPLAY NOTHING
		case '&':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		// DISPLAY 'C'
		case 'c':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		// DISPLAY 'P'
		case 'p':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'a':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'b':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'd':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);						// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);						// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		default:
			break;
	}
}
 
//static TIM_HandleTypeDef s_TimInstance = { 
//    .Instance = TIM3
//};

//void init_tim()
//{
//    __TIM3_CLK_ENABLE();
//    s_TimInstance.Init.Prescaler = 2000;
//    s_TimInstance.Init.CounterMode = TIM_COUNTERMODE_UP;
//    s_TimInstance.Init.Period = 42;
//    s_TimInstance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    s_TimInstance.Init.RepetitionCounter = 0;
//    HAL_TIM_Base_Init(&s_TimInstance);
//    HAL_TIM_Base_Start_IT(&s_TimInstance);
//	
//	  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(TIM3_IRQn);
//}

//void InitializeLED()
//{
//	__GPIOD_CLK_ENABLE();
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.Pin = GPIO_PIN_12;
//	
//	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
//	GPIO_InitStructure.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
//}

//void init_numerical_pad_GPIO(void)
//{
//	GPIO_InitTypeDef GPIO_InitDef; 								
//	SEGMENT_CLOCK_D_ENABLE;
//	
//	GPIO_InitDef.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3; 	
//	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
//	GPIO_InitDef.Pull = GPIO_NOPULL;
//	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
//	
//	HAL_GPIO_Init(GPIOD, &GPIO_InitDef);
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);
//		

//	SEGMENT_CLOCK_C_ENABLE;
//	
//	GPIO_InitDef.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11; 	
//	GPIO_InitDef.Mode = GPIO_MODE_IT_RISING;   			
//	GPIO_InitDef.Pull = GPIO_PULLDOWN;
//	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
//	
//	HAL_GPIO_Init(GPIOC, &GPIO_InitDef);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11, GPIO_PIN_RESET);
//	
//}

//void keypad_interrupt()
//{
//	
//}

//void keypad_position(int keyboard)
//{
//	
//}
