/*
 * task_default.c
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

//----------- INCLUDES ---------- //

#include "task_default.h"
#include "../Application/application.h"
#include "../Application/Display/display.h"
#include "../Application/Task_Buzzer/task_buzzer.h"
#include "../Application/Relay/relay.h"
#include "../Application/Memory/memory.h"


//----------- VARIABLES ---------- //

uint16_t blink_counter;
extern RelayStatus relay_status;
int current_cup = 0;

//----------- PRIVATE FUNCTION PROTOTYPES ---------- //


void process_auto();
void process_calibration();
void process_manual();


//----------- FUNCTIONS ---------- //

void task_default_init(void *argument) {
	blink_counter = 0;
}

void task_default_process() {



	application_process();

	osDelay(1);
}

void process_auto() {

}

void process_calibration() {

}

void process_manual() {

}
