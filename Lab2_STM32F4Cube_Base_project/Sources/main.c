//////////////////////////////////////////////
//	File Name		:main.c					//
//	Description		:program entry			//
//	Author			:Harsh Aurora, Team 12	//
//	Date			:Oct 1st, 2016			//
//////////////////////////////////////////////
	
//		Includes		//
#include <stm32f4xx_hal.h>
#include <supporting_functions.h>
#include <sysclk_config.h>
#include <gpio_example.h>
#include <adc_example.h>

// MAX COUNTER VALUES
#define COUNTERDISPLAY 2
#define COUNTERTEMP 200
#define COUNTERALARM 100
#define COUNTERPOLL 10
#define ALARM 60

//		Global variables		//
volatile int systick_flag; // flag to tell if a systick interrup has occured

// Define kalman filter struct
typedef struct kalmanstruct
{
	float q;
	float r;
	float x;
	float p;
	float k;
	float f;
	float h;
}kalmanstruct;

// 1D kalman filter function
void kalmanfilter(float* input_array, float* filtered_array, int array_len, kalmanstruct* kalmanstr) {
	for (int i = 0; i < array_len; i++) {
		// PREDICT
		kalmanstr->x = kalmanstr->f * kalmanstr->x;
		kalmanstr->p = kalmanstr->f * kalmanstr->p * kalmanstr->f + kalmanstr->q;
		
		// UPDATE
		kalmanstr->k = (kalmanstr->p * kalmanstr->h) / (kalmanstr->h * kalmanstr->p * kalmanstr->h + kalmanstr->r);
		kalmanstr->p = (1 - kalmanstr->k * kalmanstr->h) * kalmanstr->p;
		kalmanstr->x = kalmanstr->x + kalmanstr->k * (input_array[i] - kalmanstr->h * kalmanstr->x);
		
		//OUTPUT
		filtered_array[i] = kalmanstr->x;
	}
}

// Display function
void display(float temp, int display) {
	// Simple switch in order to transition between LED displays and LED off
	switch (display) {
		// Display 1
		case 0:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
							
			// CHOOSING WHAT TO DSIPLAY
			led_number((((int)temp%100)-((int)temp%10))/10, 0);
			break;
	
		// Display 2
		case 1:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
			
			// CHOOSING WHAT TO DSIPLAY			
			led_number(((int)temp%10), 1);
			break;

		// Display 3
		case 2:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
			
			// CHOOSING WHAT TO DSIPLAY
			led_number((((int)(temp*10))%1000)-(((int)temp%100)*10), 0);
			break;

		// Display 4
		case 3:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			
			// CHOOSING WHAT TO DSIPLAY
			led_char('c', 0);
			break;

		// Display nothing
		case -1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		// Default case
		default:
			break;
	}
}

// PIEZO DISPLAY FUNCTION
void piezo_display(float voltage, int led) {
	HAL_GPIO_WritePin(GPIOD, GREEN_PIN|RED_PIN|BLUE_PIN|ORANGE_PIN, GPIO_PIN_RESET);
	switch (led) {	
		// NO BREAK, THUS FOLLOWS THROUGH, NUMBER OF LED LIGHTS DEPEND ON APPLIED FORCE
		case 4:
			HAL_GPIO_WritePin(GPIOD, GREEN_PIN, GPIO_PIN_SET);
		case 3:
			HAL_GPIO_WritePin(GPIOD, ORANGE_PIN, GPIO_PIN_SET);
		case 2:
			HAL_GPIO_WritePin(GPIOD, RED_PIN, GPIO_PIN_SET);
		case 1:
			HAL_GPIO_WritePin(GPIOD, BLUE_PIN, GPIO_PIN_SET);
		case 0:
			break;

		default:
			break;
	}
}

// MAIN
int main(void) {
	// Initialization of counters, variables and kalman struct
	int display_counter = 0, temp_counter = 0, alarm_counter = 0, poll_counter = 0, time_counter = 0;
	float ADC_val, filtered_voltage, temp, ADC_piezo;
	kalmanstruct ks;
	ks.q = 0.01;
	ks.r = 25;
	ks.x = 0;
	ks.p = 1000;
	ks.k = 0;
	ks.f = 1;
	ks.h = 1;
	
  //		MCU Configuration		//
  //	Reset of all peripherals, Initializes the Flash interface and the Systick	//
  HAL_Init();
	
  //	Configure the system clock	//
  SystemClock_Config();

  //	Example code initialization	//
	gpio_led_init();
	init_segment_segments();
	init_segment_disp();
	adc_example_init();
	adc_piezo_init();

	//	run sample code forever	//
	int half_alarm_counter = COUNTERALARM / 2;
	
	while(1) {
		// run every 0.1 second. This can also be achieved with HAL_Delay(1000) for the current settengs
		if(systick_flag == 1) { // Please look in stm32f4xx_it.c to understand how this variable is set and used
			systick_flag = 0;
			
			// SAMPLE TEMPERATURE
			if(poll_counter++ >= COUNTERPOLL) {	// increments every 10 ms, used to count when 0.1 second has passed
				poll_counter = 0;
				ADC_val = adc_example();
				kalmanfilter(&ADC_val, &filtered_voltage, 1, &ks);

				ADC_piezo = adc_piezo();
			}
			
			// CONVERT TO TEMPERATURE
			if(temp_counter++ >= COUNTERTEMP) {	 // increments every 200 ms, used to count when 0.1 second has passed	
				temp_counter = 0;			
				temp = temp_conv(filtered_voltage);
				
				//printf("%f\n", temp);
				//printf("%f\n", ADC_piezo);
			}
			
			// Display functions called
			if(time_counter++ >= COUNTERDISPLAY) {	 // increments every 2 ms, used to count when 0.1 second has passed	
				time_counter = 0;
				// TOGGLE TEMPERATURE ALARM
				if (++display_counter >= 4) {
					display_counter = 0;
				}
				// Check if dangerous temperature has been reached
				if (temp < ALARM){	//ALARM TEMPERATURE SETTING	
					display(temp, display_counter);
				}
				else {
					if (alarm_counter++ >= COUNTERALARM) {	// increments every 100 ms, used to count when 0.1 second has passed
						alarm_counter = 0;
					}
					if (alarm_counter > half_alarm_counter) {	//	Toggling between display on and display off half the time
						display(temp, -1);
					}
					else {
						display(temp, display_counter);
					}
				}
			}
			
			//PIEZO DISPLAY
			if (ADC_piezo >= 0 && ADC_piezo < 6)		// Low force
				piezo_display(ADC_piezo, 0);
			else if (ADC_piezo >= 6 && ADC_piezo < 12)	// Medium force
				piezo_display(ADC_piezo, 1);
			else if (ADC_piezo >= 12 && ADC_piezo < 18)	// High force
				piezo_display(ADC_piezo, 2);
			else if (ADC_piezo >= 18 && ADC_piezo < 24)	// Maximum force
				piezo_display(ADC_piezo, 3);
			else
				piezo_display(ADC_piezo, 4);			// Display off


			// OLD TEMPERATURE ALARM USED WITHOUT PIEZO
			/*
			// TOGGLE TEMPERATURE ALARM
			if(temp >= ALARM){	//ALARM TEMPERATURE SETTING
				if(alarm_counter++ >= COUNTERALARM) { // increments every 200 ms, used to count when 0.1 second has passed			
					alarm_counter = 0;
					HAL_GPIO_WritePin(GPIOD, GREEN_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, BLUE_PIN, GPIO_PIN_SET);
				}
	
				if(alarm_counter++ >= COUNTERALARM) { // increments every 200 ms, used to count when 0.1 second has passed			
					alarm_counter = 0;			
					HAL_GPIO_WritePin(GPIOD, BLUE_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, RED_PIN, GPIO_PIN_SET);
				}
				
				if(alarm_counter++ >= COUNTERALARM) { // increments every 200 ms, used to count when 0.1 second has passed			
					alarm_counter = 0;			
					HAL_GPIO_WritePin(GPIOD, RED_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, ORANGE_PIN, GPIO_PIN_SET);
				}
				
				if(alarm_counter++ >= COUNTERALARM) { // increments every 200 ms, used to count when 0.1 second has passed			
					alarm_counter = 0;			
					HAL_GPIO_WritePin(GPIOD, ORANGE_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GREEN_PIN, GPIO_PIN_SET);
				}
			} else {
				// RESET LEDS
				HAL_GPIO_WritePin(GPIOD, GREEN_PIN|BLUE_PIN|RED_PIN|ORANGE_PIN, GPIO_PIN_RESET);
			}
			*/
		}
	}
}
