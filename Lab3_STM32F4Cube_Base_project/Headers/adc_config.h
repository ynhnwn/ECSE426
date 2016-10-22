//////////////////////////////////////////////////////////
//	File Name					: adc_config.h										//
//	Description				: header file for adc_config.h		//
//	Author						: Team 12													//
//	Date							: Oct 20th, 2016									//
//////////////////////////////////////////////////////////

#ifndef _ADC_CONFIG
#define _ADC_CONFIG

// DEFINES
#define POLL_TIMEOUT 10000

#define PIEZO_ADC	ADC2
#define PIEZO_ADC_Channel ADC_CHANNEL_11
#define PIEZO_ADC_CLK_EN __HAL_RCC_ADC2_CLK_ENABLE()

#define PIEZO_ADC_GPIO_PORT GPIOC
#define PIEZO_ADC_GPIO_PIN GPIO_PIN_1
#define PIEZO_ADC_GPIO_PORT_CLK_EN __HAL_RCC_GPIOC_CLK_ENABLE();

// PROTOTYPES
void adc_piezo_init(void);
int adc_piezo(void);

#endif /*_ADC_CONFIG*/
