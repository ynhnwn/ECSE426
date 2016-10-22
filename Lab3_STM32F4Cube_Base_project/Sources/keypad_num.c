//////////////////////////////////////////
//	File Name					: keypad_num.c		//
//	Description				: program body		//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

// INCLUDES
#include "keypad_num.h"
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "sysclk_config.h"
#include "GPIO_pins.h"

// STRUCT INITIALIZATION
GPIO_InitTypeDef GPIO_InitStructure1;
GPIO_InitTypeDef GPIO_InitStructure2;

/*
 * INITALISE THE GPIO CLK AND PIN
 * TO READ THE COLUMN OUTPUT AS THE 
 * ROW IS FILLED THROUGH
 */
void KEYPAD_GPIO_INIT_COLUMN(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitStructure1.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStructure1.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure1.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure1.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure1);
}

/* 
 * INITIALISE THE GPIO AND PIN
 * FOR THE ROW. THE ROW PINS IS
 * SET HIGH AS IT FILTERS THROUGH
 * EACH ROW. AS EACH ROW IS SET ONE
 * ONE AT A TIME SO THAT WE ARE ABLE
 * READ WHICH COLUMN WAS PUSHED
 */
void KEYPAD_GPIO_INIT_ROW(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	GPIO_InitStructure2.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStructure2.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure2.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure2.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure2);
}

/*
 * THIS FUNCTION CYCLES THROUGH THE ROW AND CHECKS
 * WHICH COLUMN IS ON DEPENDING ON WHICH ROW
 * WAS SET HIGH
 */
char keypad_swipe(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '1';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '2';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '3';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'a';
	}

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '4';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '5';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '6';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'b';
	}

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '7';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '8';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '9';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'c';
	}

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '*';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '0';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{  
		return '#';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'd';
	}
	return 'n';
}

//void KEYPAD_GPIO_INIT_BUTTON(void)
//{
//	__GPIOA_CLK_ENABLE();
//	
//	GPIO_InitStructure.Pin = GPIO_PIN_0;
//	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
//	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
//}
	
//void keypad_swipe(int row, char column)
//{	
//	switch (row){
//	
//		case 0:
//			GPIO_row_cycle(row);
//			if (column == '0'){
//				led_number(1, 0);
//				printf("keypad: 1 \n");
//			} else if (column == '1'){
//				led_number(2, 0);
//				printf("keypad: 2 \n");
//			}	else if (column == '2'){
//				led_number(3, 0);
//				printf("keypad: 3 \n");
//			}	else if (column == '3'){
//				led_char('a', 0);
//				printf("keypad: d \n");
//			}	else {
//				led_char('&', 0);
//				printf("keypad: null \n");
//			}
//			break;
//		
//		case 1:
//			GPIO_row_cycle(row);
//			if (column == '0'){
//				led_number(4, 0);
//				printf("keypad: 4 \n");
//			} else if (column == '1'){
//				led_number(5, 0);
//				printf("keypad: 5 \n");
//			}	else if (column == '2'){
//				led_number(6, 0);
//				printf("keypad: 6 \n");
//			}	else if (column == '3'){
//				led_char('b', 0);
//				printf("keypad: b \n");
//			}	else {
//				led_char('&', 0);
//				printf("keypad: null \n");
//			}
//			break;
//		
//		case 2:
//			GPIO_row_cycle(row);
//			if (column == '0'){
//				led_number(7, 0);
//				printf("keypad: 7 \n");
//			} else if (column == '1'){
//				led_number(8, 0);
//				printf("keypad: 8 \n");
//			}	else if (column == '2'){
//				led_number(9, 0);
//				printf("keypad: 9 \n");
//			}	else if (column == '3'){
//				led_char('c', 0);
//				printf("keypad: c \n");
//			}	else {
//				led_char('&', 0);
//				printf("keypad: null \n");
//			}
//			break;
//			
//		case 3:
//			GPIO_row_cycle(row);
//			if (column == '0'){
//				led_char('*', 0);
//				printf("keypad: * \n");
//			} else if (column == '1'){
//				led_number(0, 0);
//				printf("keypad: 0 \n");
//			}	else if (column == '2'){
//				led_number('#', 0);
//				printf("keypad: # \n");
//			}	else if (column == '3'){
//				led_char('d', 0);
//				printf("keypad: d \n");
//			}	else {
//				led_char('&', 0);
//				printf("keypad: null \n");
//			}
//			break;
//			
//		default:
//			break;	
//	}
//}

//char column_num_check(void)
//{
//	char column;
//	
//	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1){
//		column = '0';
//		printf("column: 0 \n");
//	} else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1){
//		column = '1';
//		printf("column: 1 \n");
//	} else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1){
//		column = '2';
//		printf("column: 2 \n");
//	} else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1){
//		column = '3';
//		printf("column: 3 \n");
//	} else {
//		column = '&';
//		printf("column: null \n");
//	}
//	
//	return column;
//}

//void GPIO_row_cycle(int row)
//{
//	switch (row){
//		
//	case 0:
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//		break;
//	
//	case 1:
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//		break;
//	
//	case 2:
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//		break;
//	
//	case 3:
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
//		break;
//	
//	default:
//		break;
//	}
