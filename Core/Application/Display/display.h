/*
 * display.h
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_


//----------- INCLUDES ---------- //
#include "main.h"

//----------- DEFINE ---------- //



//----------- ENUMS ---------- //

typedef enum {
	DISPLAY_A = 0x00, //0x00,
	DISPLAY_0 = 0xDE, //0x00,
	DISPLAY_1 = 0x82, //0x00,
	DISPLAY_2 = 0xEC, //0x00,
	DISPLAY_3 = 0xE6, //0x00,
	DISPLAY_4 = 0xB2, //0x00,
	DISPLAY_5 = 0x76, //0x00,
	DISPLAY_6 = 0x7E, //0x00,
	DISPLAY_7 = 0xC2, //0x00,
	DISPLAY_8 = 0xFE, //0x00,
	DISPLAY_9 = 0xF6, //0x00,
	DISPLAY_C = 0x5C, //0x00,
	DISPLAY_bos = 0x00, //0x00,
	DISPLAY_nokta = 0x01 //0x00,
} DISPLAY;

#define display1_active	HAL_GPIO_WritePin(DIPS1_A_GPIO_Port, DIPS1_A_Pin, GPIO_PIN_RESET);
#define display1_pasif	HAL_GPIO_WritePin(DIPS1_A_GPIO_Port, DIPS1_A_Pin, GPIO_PIN_SET);

#define display2_active HAL_GPIO_WritePin(DIPS2_A_GPIO_Port, DIPS2_A_Pin, GPIO_PIN_RESET);
#define display2_pasif HAL_GPIO_WritePin(DIPS2_A_GPIO_Port, DIPS2_A_Pin, GPIO_PIN_SET);

#define display3_active HAL_GPIO_WritePin(DIPS3_A_GPIO_Port, DIPS3_A_Pin, GPIO_PIN_RESET);
#define display3_pasif HAL_GPIO_WritePin(DIPS3_A_GPIO_Port, DIPS3_A_Pin, GPIO_PIN_SET);


//----------- PRIVATE FUNCTION PROTOTYPES ---------- //

void display_init();
void display1_show(uint8_t value);
void display2_show(uint8_t value);
void display3_show(uint8_t value);


void display_point_toggle();
void display_point_hide();
void display_show(uint8_t* disp_deger);
#endif /* INC_DISPLAY_H_ */
