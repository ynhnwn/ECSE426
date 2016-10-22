//////////////////////////////////////////
//	File Name					: kalman_1d.c			//
//	Description				: program header	//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

#ifndef _KALMAN_1D_H
#define _KALMAN_1D_H

// STRUCT DEFINE
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

// PROTOTYPE
void kalmanfilter(float*, float*, int, kalmanstruct*);

#endif /*_KALMAN_1D_H*/
