/*
 * application.h
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

//----------- INCLUDES ---------- //
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"




//----------- ENUMS ---------- //

typedef enum{
	MODE_AUTO = 0X00,
	MODE_CALIBRATION,
	MODE_MANUAL
}Mode;

typedef enum {
	BUTTON_STATUS_NONE = 0X00,
	BUTTON_STATUS_PRESSED,
	BUTTON_STATUS_RELEASED
}ButtonStatus;

typedef struct {
	uint8_t id;
	uint16_t pin;
	uint16_t duration_time;
	ButtonStatus status;
}Button;

//----------- EXTERN VARIABLES ---------- //



//-----------  VARIABLES ---------- //




//----------- FUNCTIONS ---------- //

void application_init();
void application_process();
void clear_current_button();
void display_update(uint16_t deger);



#endif /* INC_APPLICATION_H_ */
