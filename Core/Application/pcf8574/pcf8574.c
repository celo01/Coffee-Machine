/*
 * pcf8574.c
 *
 *  Created on: 20 Ara 2023
 *      Author: Alpaslan Sahan
 */
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "pcf8574.h"

#define i2c_bekle  2

void bekle_us(uint16_t us) {
	uint16_t d, i;

	for (d = 0; d < us; d++) {
		for (i = 0; i < 14; i++)
			;
	}
}

void i2c_start() {
	i2cdata_low;
	bekle_us(i2c_bekle);
	i2cclk_pasif;
	bekle_us(i2c_bekle);

}

void i2c_stop() {
	i2cdata_set;
	bekle_us(i2c_bekle);
	i2cclk_aktif;
	bekle_us(i2c_bekle);
}

void i2c_data_yaz(uint8_t deger) {
	uint8_t d = 8;
	unsigned char bit;
	while (d) {
		bit = 0x80 & deger;
		if (bit == 0x80) {
			i2cdata_set;
		} else {
			i2cdata_low;
		}
		i2cclk_aktif;
		bekle_us(i2c_bekle);
		i2cclk_pasif;
		bekle_us(i2c_bekle);
		deger = (deger << 1);
		d--;
	}
//ACK biti oku
	i2cdata_set;
	bekle_us(i2c_bekle);
	bekle_us(i2c_bekle);
	i2cclk_aktif;
	bekle_us(i2c_bekle);
	i2cclk_pasif;
	bekle_us(i2c_bekle);
}
//void i2c_cikis_10(uint8_t data) {
//
//	i2c_start();
//	i2c_data_yaz(0x40); //adres
//	i2c_data_yaz(~data);
//	i2c_stop();
//}
void i2c_cikis_1(uint8_t data) {

	i2c_start();
	i2c_data_yaz(0x42); //adres
	i2c_data_yaz(~data);
	i2c_stop();
}



