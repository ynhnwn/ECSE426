//////////////////////////////////////////////////////////
//	File Name		: main.c							//
//	Description		: header file for adc_example.h		//
//	Author			: Harsh Aurora, Team 12				//
//	Date			: Oct 1st, 2016						//
//////////////////////////////////////////////////////////

#ifndef _ADC_EXAMPLE
#define _ADC_EXAMPLE

#define POLL_TIMEOUT 10000

#define EXAMPLE_ADC ADC1
#define EXAMPLE_ADC_CHANNEL ADC_CHANNEL_TEMPSENSOR
#define EXAMPLE_ADC_CLK_EN 	__HAL_RCC_ADC1_CLK_ENABLE()

#define PIEZO_ADC	ADC2
#define PIEZO_ADC_Channel ADC_CHANNEL_11
#define PIEZO_ADC_CLK_EN __HAL_RCC_ADC2_CLK_ENABLE()


#define EXAMPLE_ADC_GPIO_PORT GPIOA
#define EXAMPLE_ADC_GPIO_PIN GPIO_PIN_5	// Pin A5 is connected to the ADC1 channel 5 input
#define EXAMPLE_ADC_GPIO_PORT_CLK_EN __HAL_RCC_GPIOA_CLK_ENABLE();	//Enabling port A clock

#define PIEZO_ADC_GPIO_PORT GPIOC
#define PIEZO_ADC_GPIO_PIN GPIO_PIN_1	// Pin C1 is connected to the ADC2 channel 11 input
#define PIEZO_ADC_GPIO_PORT_CLK_EN __HAL_RCC_GPIOC_CLK_ENABLE();	//Enabling port C clock

void adc_example_init(void);
float adc_example(void);
float temp_conv(float);
void adc_piezo_init(void);
float adc_piezo(void);
#endif
