/*
 * buzzer.c
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

//----------- INCLUDES ---------- //

#include "../Application/application.h"
#include "buzzer.h"


//----------- DEFINE ---------- //

#define TIMER_CLOCK	64000000


//----------- VARIABLES ---------- //

uint8_t prescaler = 61;
uint16_t resolution = 255;

//----------- EXTERN VARIABLES ---------- //

extern TIM_HandleTypeDef htim16;





//----------- PRIVATE FUNCTION PROTOTYPES ---------- //

void tone(uint16_t frequency, uint32_t duration);





//----------- FUNCTIONS ---------- //

void buzzer_init() {

	//htim16.Instance->ARR = resolution - 1;
	//htim16.Instance->CCR1 = 50;

	htim16.Instance->PSC = prescaler - 1;
	htim16.Instance->ARR = resolution - 1;

	//HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
}

void buzzer_play_melody1() {
	tone(4000, 100);
	tone(4000, 100);
	tone(4000, 100);
}

void buzzer_play_melody2() {
	tone(4000, 100);
	tone(4400, 100);
	tone(4200, 100);
}

void buzzer_play_melody3() {
	tone(4400, 100);
	tone(4200, 100);
	tone(4000, 100);
}

void buzzer_play_melody4() {
	tone(4000, 300);
	tone(4100, 200);
	tone(4200, 100);
}

void buzzer_play_melody5() {
	tone(4000, 250);
	tone(4100, 100);
	tone(4200, 400);
}

void buzzer_play_melody6() {
	tone(4100, 100);
	tone(4200, 200);
	tone(4300, 400);
}

void buzzer_play_melody7() {
	tone(4000, 100);
	tone(4400, 200);
	tone(4000, 100);
}

void buzzer_play_melody8() {
	tone(4400, 200);
	tone(4000, 100);
	tone(4400, 200);
}

void buzzer_play_melody9() {
	tone(4400, 300);
	tone(4300, 200);
	tone(4200, 100);
}

void buzzer_play_melodyC() {
	tone(4000, 100);
	tone(4100, 200);
	tone(4200, 300);
}
void tone(uint16_t frequency, uint32_t duration) {

	int prescaler = TIMER_CLOCK / (frequency * resolution);
	htim16.Instance->PSC = prescaler - 1;
	htim16.Instance->ARR = resolution - 1;

	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	osDelay(duration);
	HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
}
