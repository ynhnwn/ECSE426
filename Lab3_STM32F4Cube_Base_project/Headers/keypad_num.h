//////////////////////////////////////////
//	File Name					: keypad_num.h		//
//	Description				: program header	//
//	Author						: Team 12					//
//	Date							: Oct 20th, 2016	//
//////////////////////////////////////////

#ifndef _KEYPAD_NUM_H
#define _KEYPAD_NUM_H

// PROTOTYPES
void KEYPAD_GPIO_INIT_COLUMN(void);
void KEYPAD_GPIO_INIT_ROW(void);
char keypad_swipe(void);

//void keypad_swipe(int, char);
//char column_num_check(void);
//void GPIO_row_cycle(int);

#endif /*_KEYPAD_NUM_H*/
