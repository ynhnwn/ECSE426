//////////////////////////////////////////
//	File Name					: main.c					//
//	Description				: program entry		//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////
	
#include "main.h"

extern TIM_HandleTypeDef TIM_Handle;
extern TM_LIS302DL_t Axis_Data;
extern int TIM_flag;

// Main
int main(void)
{
	// CYCLING COUNTERS
 	int display_counter = 0, time_counter = 0, poll_counter = 0, cycling_counter = 0, cycling_pad = 0, print_counter = 0,  piezo_v;
	float accel_lis3dsh;
	
	// INITIALIZATION
	HAL_Init();
	gpio_led_init();
	InitializeTIM();
	SystemClock_Config();
	init_acc_GPIO_setup();
	
	KEYPAD_GPIO_INIT_COLUMN();
	KEYPAD_GPIO_INIT_ROW();
	
	InitializeTIM_LED();
	init_segment_disp();
	init_segment_segments();
	
//	init_acc_GPIO_setup();
	init_acc_setup();
	adc_piezo_init();
	
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	// INFINITE WHILE LOOP
	while (1)
	{	
		// HARDWARE TIMER COUNTER
		if(TIM_flag == 1)
		{
			TIM_flag = 0;		
			
			// POLL CYCLING
			if(poll_counter++ >= COUNTERPOLL)			// increments every 10 ms, used to count when 0.1 second has passed
			{
				poll_counter = 0;
				
				// POLL PIEZO, ACCELEROMETER
				piezo_v = adc_piezo();
				LIS3DSH_ReadACC(&accel_lis3dsh);
				read_axis();
			}
			
			// KEYPAD CYCLING
			if(cycling_counter++ >= CYCLINGPOLL)	// increments every 2 ms, used to count when 0.1 second has passed	
			{
				cycling_counter = 0;
				if (++cycling_pad >= 4)							//CYCLING BETWEEN THE 4 ROWS OF THE KEYPAD
				{
					cycling_pad = 0;
				}
			}
			
			// DISPLAY CYCLING
			if(time_counter++ >= COUNTERDISPLAY)	// increments every 2 ms, used to count when 0.1 second has passed	
			{
				time_counter = 0;
				if (++display_counter >= 4) 				//CYCLING BETWEEN THE 4 LED DISPLAYS
				{
					display_counter = 0;
				}
				display(piezo_v, display_counter);
			}
			
			// PRINT CYCLING
			if(print_counter++ >= PRINTING)				// increments every 2 ms, used to count when 0.1 second has passed	
			{
				print_counter = 0;
				printf("[Acceleration: %f]\t[Axis x: %d] [Axis y: %d] [Axis z: %d]\n", accel_lis3dsh, Axis_Data.X, Axis_Data.Y, Axis_Data.Z);
				if(keypad_swipe() != 'n')						//PRINT ONLY IF PRESSED
				{
					printf("Key: %c\n", keypad_swipe());
				}
				printf("\n");
			}
		}
	}
}
