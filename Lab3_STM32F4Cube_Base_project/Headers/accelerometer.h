//////////////////////////////////////////
//	File Name				: accelerometer.h		//
//	Description			: program Header		//
//	Author					: Team 12						//
//	Date						: Oct 20th, 2016		//
//////////////////////////////////////////

#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

// INCLUDE
#include "arm_math.h"

// STRUCT INITIALIZATION
typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
} TM_LIS302DL_t;

// PROTOTYPES
void read_axis(void);

#endif /*_ACCELEROMETER_H*/
