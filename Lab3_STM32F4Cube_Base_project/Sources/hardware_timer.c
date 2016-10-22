////////////////////////////////////////////
//	File Name					: hardware_timer.c	//
//	Description				: program entry			//
//	Author						: Team 12						//
//	Date							: Oct 20th, 2016		//
////////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "sysclk_config.h"
#include "hardware_timer.h"

// INITIALIZATION OF VARABLE AND STUCT
int TIM_flag;
TIM_HandleTypeDef TIM_Handle;

// INITIALIZE TIM3 
void InitializeTIM()
{
	__TIM3_CLK_ENABLE();
	
	// PERIOD*PRESCALAR CANNOT EXCEED 16BIT (TIM3)
	TIM_Handle.Instance = TIM3;
	TIM_Handle.Init.Prescaler = 200;													// PRESCALAR OF 200
	TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Handle.Init.Period = 82;															// PERIOD OF 82
	TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Handle.Init.RepetitionCounter = 0;
	
	HAL_TIM_Base_Init(&TIM_Handle);
	HAL_TIM_Base_Start_IT(&TIM_Handle);
}

// TIM_LED INITIALIZATION, FOR TESTING
void InitializeTIM_LED()
{
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

// CALLBACK FUNCTION, TIME THE IRQHANDLER IS CALLED
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// CHECK FOR TIMER INSTANCE
	if(htim -> Instance == TIM3)
	{
		TIM_flag = 1; //SET FLAG TO BE USED IN MAIN
	}
}
