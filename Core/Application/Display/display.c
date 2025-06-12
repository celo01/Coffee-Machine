/*
 * display.c
 *
 *  Created on: Feb 1, 2023
 *      Author: alpdade
 */



//----------- INCLUDES ---------- //
#include "display.h"
#include "../Application/application.h"
#include "../Application/pcf8574/pcf8574.h"
#include <stdint.h>
#include <stdbool.h>

//----------- VARIABLES ---------- //

volatile bool toggle_flag = false;

extern Button buttons[3];
extern uint8_t ayarMode;
extern uint8_t gosterimdekiDeger;  // application.c’de tanımlı

//----------- FUNCTIONS ---------- //

void display_init() {



}

void bekle (uint8_t deger)
{
	for (uint8_t i=0;i<deger;++i)
	{
	//for (uint8_t c=0;c<2;++c);
	}
}

void display1_show(uint8_t value) {

	switch (value)
	{
	    case 0:
	    	i2c_cikis_1(DISPLAY_0);
	    break;
	    case 1:
	       	i2c_cikis_1(DISPLAY_1);
	    break;
	    case 2:
	        i2c_cikis_1(DISPLAY_2);
	    break;
	    case 3:
	    	i2c_cikis_1(DISPLAY_3);
	    break;
	    case 4:
	       	i2c_cikis_1(DISPLAY_4);
	    break;
	    case 5:
	        i2c_cikis_1(DISPLAY_5);
	    break;
	    case 6:
	    	i2c_cikis_1(DISPLAY_6);
	    break;
	    case 7:
	       	i2c_cikis_1(DISPLAY_7);
	    break;
	    case 8:
	        i2c_cikis_1(DISPLAY_8);
	    break;
	    case 9:
	    	i2c_cikis_1(DISPLAY_9);
	    break;
	    case 0XA:
	       	i2c_cikis_1(~DISPLAY_A);
	    break;
	    case 0Xb:
	       	i2c_cikis_1(DISPLAY_bos);
	    break;
	    case 0Xc:
	       	i2c_cikis_1(~DISPLAY_nokta);
	    break;
	}

//	    case 0XA:
//	       	i2c_cikis_1(~DISPLAY_A);
//	    break;
//	    case 0Xc:
//	       	i2c_cikis_1(DISPLAY_bos);
//	    break;
//	    case 0Xb:
//	   	       	i2c_cikis_1(~DISPLAY_nokta);
//	   	    break;

	display1_active;
	display2_pasif;
	display3_pasif;

	bekle(2);

}

void display2_show(uint8_t value) {

	//value |= 0x01;
	switch (value)
	{
    case 0:
    	 i2c_cikis_1(DISPLAY_0 | 0x01);
    break;
    case 1:
    	i2c_cikis_1(DISPLAY_1  | 0x01);
    break;
    case 2:
    	i2c_cikis_1(DISPLAY_2  | 0x01);
    break;
    case 3:
    	i2c_cikis_1(DISPLAY_3  | 0x01);
    break;
    case 4:
    	i2c_cikis_1(DISPLAY_4  | 0x01);
    break;
    case 5:
    	i2c_cikis_1(DISPLAY_5  | 0x01);
    break;
    case 6:
    	i2c_cikis_1(DISPLAY_6  | 0x01);
    break;
    case 7:
    	i2c_cikis_1(DISPLAY_7  | 0x01);
    break;
    case 8:
    	i2c_cikis_1(DISPLAY_8  | 0x01);
    break;
    case 9:
    	i2c_cikis_1(DISPLAY_9  | 0x01);
    break;
    case 0Xb:
       	i2c_cikis_1(DISPLAY_bos);
    break;
    case 0Xc:
       	i2c_cikis_1(~DISPLAY_nokta);
    break;
	}
	display1_pasif;
	display2_active;
	display3_pasif;

	bekle(2);
}


void display3_show(uint8_t value) {

    bool wantDot = false;
    if ( (ayarMode == 2) ||
         (ayarMode == 0 && gosterimdekiDeger == 2) )
    {
        wantDot = true;
    }

    switch (value)
    {
        case 0:
            if(wantDot) { i2c_cikis_1(DISPLAY_0 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_0);        }
        break;

        case 1:
            if(wantDot) { i2c_cikis_1(DISPLAY_1 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_1);        }
        break;

        case 2:
            if(wantDot) { i2c_cikis_1(DISPLAY_2 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_2);        }
        break;

        case 3:
            if(wantDot) { i2c_cikis_1(DISPLAY_3 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_3);        }
        break;

        case 4:
            if(wantDot) { i2c_cikis_1(DISPLAY_4 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_4);        }
        break;

        case 5:
            if(wantDot) { i2c_cikis_1(DISPLAY_5 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_5);        }
        break;

        case 6:
            if(wantDot) { i2c_cikis_1(DISPLAY_6 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_6);        }
        break;

        case 7:
            if(wantDot) { i2c_cikis_1(DISPLAY_7 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_7);        }
        break;

        case 8:
            if(wantDot) { i2c_cikis_1(DISPLAY_8 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_8);        }
        break;

        case 9:
            if(wantDot) { i2c_cikis_1(DISPLAY_9 | 0x01); }
            else        { i2c_cikis_1(DISPLAY_9);        }
        break;

        case 0xA:
            // Örnek “A” karakteri; noktayla birlikte mi olsun istersiniz?
            if(wantDot) { i2c_cikis_1(~DISPLAY_A | 0x01); }
            else        { i2c_cikis_1(~DISPLAY_A);        }
        break;

        case 0x0b:  // Boş (blank) gösterim
            // Nokta eklemek mantıklı mı, karar size ait.
            // Burada genelde noktasız bırakmak isteyebilirsiniz:
            i2c_cikis_1(DISPLAY_bos);
        break;

        case 0x0c:  // ~DISPLAY_nokta (sadece nokta)
            // Yine “dot içinde dot” gibi olmaması için
            // genelde burayı da olduğu gibi bırakmak istersiniz.
            i2c_cikis_1(~DISPLAY_nokta);
        break;
    }
	display1_pasif;
	display2_pasif;
	display3_active;

	bekle(2);
}

void display_show(uint8_t* disp_deger) {
	display1_show(disp_deger[0]);
	display2_show(disp_deger[1]);
	display3_show(disp_deger[2]);
}
