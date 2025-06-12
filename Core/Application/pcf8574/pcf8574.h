/*
 * pcf8574.h
 *
 *  Created on: 20 Ara 2023
 *      Author: Alpaslan Sahan
 */

#ifndef APPLICATION_PCF8574_PCF8574_H_
#define APPLICATION_PCF8574_PCF8574_H_
#include "main.h"


#define i2cdata_low   HAL_GPIO_WritePin(i2c_sda_GPIO_Port, i2c_sda_Pin, GPIO_PIN_RESET)
#define i2cdata_set   HAL_GPIO_WritePin(i2c_sda_GPIO_Port, i2c_sda_Pin, GPIO_PIN_SET)

#define i2cclk_pasif   HAL_GPIO_WritePin(i2c_scl_GPIO_Port, i2c_scl_Pin, GPIO_PIN_RESET)
#define i2cclk_aktif   HAL_GPIO_WritePin(i2c_scl_GPIO_Port, i2c_scl_Pin, GPIO_PIN_SET)

#define displey1_set   HAL_GPIO_WritePin(DIPS1_A_GPIO_Port, DIPS1_A_Pin, GPIO_PIN_SET)
#define displey1_low   HAL_GPIO_WritePin(DIPS1_A_GPIO_Port, DIPS1_A_Pin, GPIO_PIN_RESET)

#define displey2_low   HAL_GPIO_WritePin(DIPS2_A_GPIO_Port, DIPS2_A_Pin, GPIO_PIN_RESET)
#define displey2_set   HAL_GPIO_WritePin(DIPS2_A_GPIO_Port, DIPS2_A_Pin, GPIO_PIN_SET)

#define displey3_low   HAL_GPIO_WritePin(DIPS3_A_GPIO_Port, DIPS3_A_Pin, GPIO_PIN_RESET)
#define displey3_set   HAL_GPIO_WritePin(DIPS3_A_GPIO_Port, DIPS3_A_Pin, GPIO_PIN_SET)

#define segment_0 0xf6

void i2c_cikis_1(uint8_t data);

#endif /* APPLICATION_PCF8574_PCF8574_H_ */
