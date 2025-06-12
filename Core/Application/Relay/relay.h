/*
 * relay.h
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#include "main.h"




//----------- EXTERN VARIABLES ---------- //



//----------- ENUMS ---------- //

typedef enum {
	RELAY_RELEASED = 0x00,
	RELAY_PULLED
}RelayStatus;


//----------- FUNCTIONS DECLARATION ---------- //

void relay_init();
void relay_pull();
void relay_release();

#endif /* INC_RELAY_H_ */
