#include <stdio.h>


struct kalman_state kalman;	


int Kalmanfilter_c(float* InputArray, float* OutputAray, kalman_state* kstate, int Lenght, int State_dimension, int Measurement_dimension){
	
}


struct kalman_state{
	float	f,h,q,r,x,p,k;			/*Kalman states*/	
} kalman_state;

float* predict (float* InputArray, float* OutputArray, 

