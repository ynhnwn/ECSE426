//////////////////////////////////////////
//	File Name					: accelerometer.c	//
//	Description				: program entry		//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "lis3dsh.h"
#include "accelerometer.h"
#include "supporting_functions.h"

// INITIALIZE STRUCT (THIS IS A STRUCT THAT WE CAN CALL TO READ THE AXIS (X, Y, AND Z)
TM_LIS302DL_t Axis_Data;

// READ AXIS FUNCTION
/*
 * BECAUSE LIS3DSH ONLY OUTPUTS ACCELERATION OF THE AXIS
 * X, Y AND Z INTO TWO 8 BITS (HIGH SIDE AND LOW SIDE). AS
 * SUCH, WE SHIFT THE LOW SIDE BY 8 BIT THEN OR THE HIGH
 * SIDE TO CREAT THE 16 BITS TO READ THE VALUE.
 */
void read_axis(void)
{
	uint8_t buffer[6];

	//READING VALUES
	LIS3DSH_Read(&buffer[0], LIS3DSH_OUT_X_L, 1);
	LIS3DSH_Read(&buffer[1], LIS3DSH_OUT_X_H, 1);
	LIS3DSH_Read(&buffer[2], LIS3DSH_OUT_Y_L, 1);
	LIS3DSH_Read(&buffer[3], LIS3DSH_OUT_Y_H, 1);
	LIS3DSH_Read(&buffer[4], LIS3DSH_OUT_Z_L, 1);
	LIS3DSH_Read(&buffer[5], LIS3DSH_OUT_Z_H, 1);
	
	// SET AXIS
	Axis_Data.X = (int16_t)((buffer[1] << 8) + buffer[0])*LIS3DSH_SENSITIVITY_2G;
	Axis_Data.Y = (int16_t)((buffer[3] << 8) + buffer[2])*LIS3DSH_SENSITIVITY_2G;
	Axis_Data.Z = (int16_t)((buffer[5] << 8) + buffer[4])*LIS3DSH_SENSITIVITY_2G;
}
