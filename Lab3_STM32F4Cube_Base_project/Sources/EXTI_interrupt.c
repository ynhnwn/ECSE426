////////////////////////////////////////////
//	File Name					: EXTI_interrupt.c	//
//	Description				: program entry			//
//	Author						: Team 12						//
//	Date							: Oct 20th, 2016		//
////////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "sysclk_config.h"
#include "lis3dsh.h"
#include "sysclk_config.h"
#include "EXTI_interrupt.h"

// STRUCT INITIALIZATION
GPIO_InitTypeDef GPIO_Init;
LIS3DSH_InitTypeDef LIS3DSH_InitType;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_DRYInterrupt;

// 
void init_acc_GPIO_setup(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_Init.Pin = GPIO_PIN_0; 	
	GPIO_Init.Mode = GPIO_MODE_IT_RISING;   			
	GPIO_Init.Pull = GPIO_PULLDOWN;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(GPIOE, &GPIO_Init);
	
	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

// SETTING UP THE ACCELEROMETER AND PASSING THE INITIAL SETING
// WE ALSO SET THE INT1 PIN LOCATED ON GPIOE GPIO_PIN_0 USED FOR INTERRUPTS
void init_acc_setup(void)
{
	LIS3DSH_InitType.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_25;
	LIS3DSH_InitType.Axes_Enable = LIS3DSH_XYZ_ENABLE;
	LIS3DSH_InitType.AA_Filter_BW = LIS3DSH_AA_BW_200;
	LIS3DSH_InitType.Self_Test = LIS3DSH_SELFTEST_NORMAL;
	LIS3DSH_InitType.Continous_Update = LIS3DSH_ContinousUpdate_Enabled;
	LIS3DSH_InitType.Full_Scale = LIS3DSH_FULLSCALE_2;
	LIS3DSH_Init(&LIS3DSH_InitType);
	
	LIS3DSH_DataRateCmd(LIS3DSH_DATARATE_25);
	
	LIS3DSH_DRYInterrupt.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_DISABLED;
//	LIS3DSH_DRYInterrupt.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
//	LIS3DSH_DRYInterrupt.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED;
	LIS3DSH_DataReadyInterruptConfig(&LIS3DSH_DRYInterrupt);
}

// EXTI CALLBACK FUNCTION, CALLED EVERY TIME THE IRQHANDLER IS CALLED
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	printf("interrupt detected\n");
//	if(GPIO_Pin == GPIO_PIN_0)
//	{
//		printf("interrupt detected\n");
//	}
}
