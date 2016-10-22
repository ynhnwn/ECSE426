#include <stdio.h>
#include <math.h>
#include "arm_math.h"
//#include "kalman_filter.h"

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

const int32_t length_in_out=5;
const int32_t dimension=1;

typedef struct kalman_state
{
	float32_t m_q[dimension*dimension];
	float32_t m_r[dimension*dimension];
	float32_t v_x[dimension];
	float32_t m_p[dimension*dimension];
	float32_t m_k[dimension*dimension];
	float32_t m_f[dimension*dimension];
	float32_t m_h[dimension*dimension];
}kalman_state;

// Identity matrix 
float32_t identity_mx[dimension*dimension];

// Output of kalmanfilter
float32_t output_state_x[dimension*length_in_out];

// Measured State
const float32_t matrix_z[dimension*length_in_out]={
	1.1, 1.2, 1.3, 1.4, 2.6
};

extern void kalmanfilterasm(float* input_array, float* filtered_array, int array_len, kalmanstruct* kalmanstr);

// Sourced from Armens' Group (thanks for your help) (fetching the column value of an array)
void vector_matrix(float* output_vector, float* input_matrix, int meas_dim, int length, int col)
{
	int j = 0;
	for(int i = col; i < meas_dim * length; i += length){
		*(output_vector + j) = *( input_matrix + i);
		j++;
	}
} 
void update_col(float* x_array, float* x, int state_dimension, int Length, int col)
{
	for(int i = 0; i < state_dimension; i++)
		*(x + i*Length + col) = *(x_array + i);
}

void assign(float* ks, float value, int dimension)
{
	for (int i =0; i< dimension; i++)
		*(ks + i) = value;
}

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int Length, int State_dimension, int Measurement_dimension){
	
	// Setting parameter for caculations
	float32_t input_z_32[State_dimension*Length];
	float32_t output_x_32[Measurement_dimension*Length];
	float32_t f_trans_32[State_dimension*State_dimension];
	float32_t h_trans_32[State_dimension*State_dimension];
	float32_t vector1_32[Measurement_dimension];
	float32_t vector2_32[Measurement_dimension];
	float32_t vectro3_32[Measurement_dimension];
	float32_t matrix1_32[State_dimension*State_dimension];
	float32_t matrix2_32[State_dimension*State_dimension];
	float32_t x_kk_1_32[Measurement_dimension];
	
	// Initalisation of parameters
	arm_matrix_instance_f32 r;
	arm_matrix_instance_f32 p;
	arm_matrix_instance_f32 q;
	arm_matrix_instance_f32 x;
	arm_matrix_instance_f32 f;
	arm_matrix_instance_f32 h;
	arm_matrix_instance_f32 k;
	arm_matrix_instance_f32 f_trans;
	arm_matrix_instance_f32 h_trans;
	arm_matrix_instance_f32 I;
	arm_matrix_instance_f32 z_vector;

	arm_matrix_instance_f32 vector1;
	arm_matrix_instance_f32 vector2;
	arm_matrix_instance_f32 vector3;
	arm_matrix_instance_f32 matrix1;
	arm_matrix_instance_f32 matrix2;

	arm_matrix_instance_f32 x_kk_1;
	
	arm_mat_init_f32(&p, State_dimension, State_dimension, (float32_t *)kstate->m_p);
	arm_mat_init_f32(&q, State_dimension, State_dimension, (float32_t *)kstate->m_q);
	arm_mat_init_f32(&r, State_dimension, State_dimension, (float32_t *)kstate->m_r);
	arm_mat_init_f32(&f, State_dimension, State_dimension, (float32_t *)kstate->m_f);
	arm_mat_init_f32(&h, State_dimension, State_dimension, (float32_t *)kstate->m_h);
	arm_mat_init_f32(&k, State_dimension, State_dimension, (float32_t *)kstate->m_k);
	arm_mat_init_f32(&I, State_dimension, State_dimension, (float32_t *)identity_mx);
	arm_mat_init_f32(&x, Measurement_dimension, 1, (float32_t *)output_x_32);
	arm_mat_init_f32(&f_trans, State_dimension, State_dimension, (float32_t *)f_trans_32);
	arm_mat_init_f32(&h_trans, State_dimension, State_dimension, (float32_t *)h_trans_32);

	arm_mat_init_f32(&vector1, State_dimension, 1, (float32_t *)vector1_32);
	arm_mat_init_f32(&vector2, State_dimension, 1, (float32_t *)vector2_32);
	arm_mat_init_f32(&vector3, State_dimension, 1, (float32_t *)vector3_32);
	arm_mat_init_f32(&matrix1, State_dimension, State_dimension, (float32_t *)matrix1_32);
	arm_mat_init_f32(&matrix2, State_dimension, State_dimension, (float32_t *)matrix2_32);

	arm_mat_init_f32(&z_vector, State_dimension, 1, (float32_t *)input_z_32);

	// Set transposes for F and H
	arm_mat_trans_f32(&f_trans, State_dimension, State_dimension, &f);
	arm_mat_trans_f32(&h_trans, State_dimension, State_dimension, &h);

	for(int i=0; i < Length; i++){
		vector_matrix(input_z_32, (float32_t *)matrix_z, Measurement_dimension, Length, i);

		// x_k|k-1 = Fx_k-1|k-1
		arm_mat_mult_f32(&f, &x, &vector1);										// Output Xk|k-1
		arm_copy_f32(vector1_32, x_kk_1_32, State_dimension);					// Pass result to Xk|k-1
	
		// Pk|k-1
		arm_mat_mult_f32(&f, &p, &matrix1);
		arm_mat_mult_f32(&matrix1, &f_trans, &matrix2);
		arm_mat_add_f32(&matrix2, &q, &p);
	
		// K new
		arm_mat_mult_f32(&h, &p, &matrix1);
		arm_mat_mult_f32(&matrix1, &h_trans, &matrix2);
		arm_mat_add_f32(&matrix2, &r, &matrix1);
		arm_mat_mult_f32(&p, &h_trans, &matrix2);
		arm_mat_mult_f32(&matrix2, &matrix1, &k);
	
		// Pk|k
		arm_mat_mult_f32(&k, &h, &matrix1);
		arm_mat_sub_f32(&I, &matrix1, &matrix2);
		arm_mat_mult_f32(&matrix2, &p, &matrix1);
		arm_copy_f32(matrix1_32, kstate->m_p, (State_dimension*State_dimension));
	
		// x_k|k
		arm_mat_mult_f32(&h, &x, &vector1);
		arm_mat_sub_f32(&z_vector, &vector1, &vector2);
		arm_mat_mult_f32(&k, &vector2, &vector1);
		arm_mat_add_f32(&x, &vector1, &x);
		update_col(x, OutputArray, State_dimension, Length, c);
	}
}

int main(void)
{
	kalman_state k_s;
	
	assign(k_s.m_r, 0.1, dimension);
	assign(k_s.m_p, 0.1, dimension);
	assign(k_s.m_q, 0.1, dimension);
	assign(k_s.m_f, 0.8, dimension);
	assign(k_s.m_h, 1.2, dimension);
	assign(k_s.m_k, 0, dimension);
	assign((float32_t *)identity_mx, 1.0, dimension);

	arm_status status = Kalmanfilter_C((float32_t *)matrix_z, (float32_t *)output_state_x, &k_s, length_in_out, dimension, dimension);

	return 0;
}