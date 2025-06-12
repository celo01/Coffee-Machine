#ifndef APPLICATION_DEGISKENLER_H_
#define APPLICATION_DEGISKENLER_H_

#include "main.h"

typedef struct
{
    uint8_t digit1;
    uint8_t digit2;
    uint8_t digit3;
} SaveReg_t;

extern SaveReg_t Save_reg;

extern uint32_t zaman_count;
extern uint32_t zaman_count100;
extern uint8_t zaman_say;
extern uint8_t zaman_durdur;
extern uint16_t disp_flasor;
extern uint16_t sayim_timer;

extern uint8_t mod1_digit2;
extern uint8_t mod1_digit3;
extern uint8_t mod2_digit1;
extern uint8_t mod2_digit2;
extern uint8_t mod2_digit3;

#define buton1  (HAL_GPIO_ReadPin(BUT1_GPIO_Port, BUT1_Pin)==0)
#define buton2  (HAL_GPIO_ReadPin(BUT2_GPIO_Port, BUT2_Pin)==0)
#define buton3  (HAL_GPIO_ReadPin(BUT3_GPIO_Port, BUT3_Pin)==0)
#define buton4  (HAL_GPIO_ReadPin(BUT4_GPIO_Port, BUT4_Pin)==0)
#define switch1 (HAL_GPIO_ReadPin(switch_GPIO_Port, switch_Pin)==0)
#define role    (HAL_GPIO_ReadPin(RELAY_GPIO_Port, RELAY_Pin)==0)

extern uint16_t disp_flasor;

#endif /* APPLICATION_DEGISKENLER_H_ */
