/*
 * task_buzzer.c
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */
//----------- INCLUDES ---------- //

#include "task_buzzer.h"
#include "../Application/application.h"
#include "../Application/Buzzer/buzzer.h"


//----------- VARIABLES ---------- //


BUZZER_STATUS buzzer_status;


//----------- FUNCTIONS ---------- //

void task_buzzer_init(void *argument) {

	buzzer_status = BUZZER_NONE;
	buzzer_init();
    buzzer_status = BUZZER_PLAY_MELODY_1;
}

void task_buzzer_process() {
	switch (buzzer_status) {
	case BUZZER_NONE:
		break;
	case BUZZER_PLAY_MELODY_1:
		buzzer_play_melody1();
		break;
	case BUZZER_PLAY_MELODY_2:
		buzzer_play_melody2();
		break;
	case BUZZER_PLAY_MELODY_3:
		buzzer_play_melody3();
		break;
	case BUZZER_PLAY_MELODY_4:
		buzzer_play_melody4();
		break;
	case BUZZER_PLAY_MELODY_5:
		buzzer_play_melody5();
	default:
		break;
	}
	buzzer_status = BUZZER_NONE;
}
