/*
 * task_buzzer.c
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

#ifndef INC_TASK_BUZZER_C_
#define INC_TASK_BUZZER_C_


//----------- ENUMS ---------- //

typedef enum {
	BUZZER_NONE = 0x00,
	BUZZER_PLAY_MELODY_1,
	BUZZER_PLAY_MELODY_2,
	BUZZER_PLAY_MELODY_3,
	BUZZER_PLAY_MELODY_4,
	BUZZER_PLAY_MELODY_5,
	BUZZER_PLAY_MELODY_6,
	BUZZER_PLAY_MELODY_7,
	BUZZER_PLAY_MELODY_8,
	BUZZER_PLAY_MELODY_9,

} BUZZER_STATUS;

//----------- EXTERN VARIABLES ---------- //

extern BUZZER_STATUS buzzer_status;


//----------- FUNCTIONS DECLARATION ---------- //

void task_buzzer_init();
void task_buzzer_process();

#endif /* INC_TASK_BUZZER_C_ */
