/*
 * memory.h
 *
 *  Created on: Feb 2, 2023
 *      Author: alpdade
 */

#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "main.h"
#include <stdint.h>



typedef struct
{
    uint32_t validFlag;      // Geçerli veri olduğunu anlamak için bir işaret (örn. 0xDEADFACE).
    uint8_t  mod1_digit2;
    uint8_t  mod1_digit3;
    uint8_t  mod2_digit1;
    uint8_t  mod2_digit2;
    uint8_t  mod2_digit3;
    uint8_t  _reserved[3];
} MemoryData_t;



//uint8_t read_addr();
//void save_new_addr(uint8_t addr);
//void eeprom_yaz(void);

void memory_init_values(void);   // Uygulama başlarken hafızadan oku
void memory_save_values(void);   // Ayar modundan çıkarken hafızaya yaz

#endif /* INC_MEMORY_H_ */
