//////////////////////////////////////////////////
//	File Name					: main.h									//
//	Description				: header file for main.c	//
//	Author						: Team 12									//
//	Date							: Oct 1st, 2016						//
//////////////////////////////////////////////////

// INCLUDES
#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "lis3dsh.h"
#include "supporting_functions.h"
#include "sysclk_config.h"
#include "GPIO_pins.h"
#include "adc_config.h"
#include "hardware_timer.h"
#include "accelerometer.h"
#include "EXTI_interrupt.h"
#include "keypad_num.h"

// COUNTER VALUES
#define COUNTERDISPLAY 2
#define COUNTERPOLL 1000
#define CYCLINGPOLL 500
#define PRINTING 1000

#endif /*_MAIN_H*/
