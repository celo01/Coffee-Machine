/*
 * application.c
 * Created on: Feb 1, 2023
 * Author: Celil BAYRAKDAR (Revize)
 */

//----------- INCLUDES ---------- //
#include "main.h"
#include "cmsis_os.h"           // FreeRTOS kullanılıyorsa bu header gerekir
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "application.h"        // Bu dosyanın kendi header'ı
#include "degiskenler.h"        // Projenin genel değişkenlerinin tanımlı olduğu dosya
#include "../Application/Display/display.h"  // Display gösterim fonksiyonları
#include "../Application/Buzzer/buzzer.h"    // Buzzer fonksiyonları
#include "../Application/Relay/relay.h"      // Röle (relay) fonksiyonları
#include "../Application/Memory/memory.h"    // Bellek ile ilgili fonksiyonlar (varsa)
#include "../Application/pcf8574/pcf8574.h"  // PCF8574 arayüzü (varsa)

//----------- VARIABLES ---------- //

extern uint16_t disp_flasor;

uint8_t switch1_previous = 0;
// display_value: 7-segmentlerde gösterilecek haneleri tutar (digit1, digit2, digit3, vb.)
uint8_t display_value[4];

// Bazı bayraklar ve sayaçlarda kullanılan değişkenler
bool buttons_enabled = false;
uint8_t mode = 0;
uint16_t flag = 0;

// Normal modda kullanılan 3 hane (ekrandaki esas değer)
uint8_t digit1, digit2, digit3;

// Geri sayım aktif mi?
uint8_t gerisayimAktif = 0;

// Zaman sayacı
extern uint16_t sayim_timer;

// Kısa basma bayrağı
bool button4_short_press = false;

// Ayar modları:
//  0 => Normal mod
//  1 => Mod1 (2 haneli ayar: mod1_digit2, mod1_digit3)
//  2 => Mod2 (3 haneli ayar: mod2_digit1, mod2_digit2, mod2_digit3)
uint8_t ayarMode = 0;

// Normal modda hangi değeri gösterip geri sayıyoruz?
//  0 => hiçbirini
//  1 => Mod1 (2 haneli)
//  2 => Mod2 (3 haneli)
uint8_t gosterimdekiDeger = 0;

// Mod1 değişkenleri
extern uint8_t mod1_digit2;
extern uint8_t mod1_digit3;

// Mod2 değişkenleri
extern uint8_t mod2_digit1;
extern uint8_t mod2_digit2;
extern uint8_t mod2_digit3;

//----------- PRIVATE FUNCTION PROTOTYPES ---------- //
void buton_kontrol(void);
void ayar_modu_islemleri(void);
void degerGoster(void);
void degerSifiraSay(void);

//----------- FUNCTIONS ---------- //

/**
 * @brief application_init
 *        Uygulama başlatıldığında yapılacak ilk ayarları içerir.
 */
void application_init(void)
{

    memory_init_values();

}

/**
 * @brief buton_kontrol
 *        Buton1, Buton2, Buton3, Buton4’ü okuyarak ilgili mantıkları işletir.
 */
void buton_kontrol(void)
{
    // ---- BUTON4 her zaman kontrol edilsin ----
    // Geri sayım olsa bile buton4 aktif (ayar moduna geçebilmek için)
    if (buton4)
    {
        osDelay(10);
        if ((flag & 0x10) == 0)
        {
            flag |= 0x10;

            ayarMode++;
            if (ayarMode > 2) {
                ayarMode = 0;
                memory_save_values();
            }

            // Geri sayımı sıfırla (isterseniz)
            gerisayimAktif = 0;
        }
    }
    else
    {
        flag &= ~0x10;
    }

    // ---- EĞER GERI SAYIM AKTIFSE, BUTON1-2-3'Ü HİÇBİR ŞEKİLDE İŞLEME ----
    // Sadece buton4 haricindeki her şeyi return diyerek iptal edebilirsiniz.
    if (gerisayimAktif == 1) {
        return;  // Buton1,2,3 kontrolüne girmeden fonksiyondan çık.
    }

    // ---- BUTON1 ----
    if (buton1)
    {
        osDelay(10);
        if ((flag & 0x02) == 0)
        {
            flag |= 0x02;

            if (ayarMode == 1) {
                // Mod1 ayar
            }
            else if (ayarMode == 2) {
                // Mod2 ayar => mod2_digit1++
                mod2_digit1++;
                if (mod2_digit1 >= 10) {
                    mod2_digit1 = 0;
                }
            }
            else {
                // Normal mod => BUTON1 => Mod1 göster + geri say
                gosterimdekiDeger = 1;
                degerGoster();
                degerSifiraSay();
            }
        }
    }
    else
    {
        flag &= ~0x02;
    }

    // ---- BUTON2 ----
    if (buton2)
    {
        osDelay(10);
        if ((flag & 0x04) == 0)
        {
            flag |= 0x04;

            if (ayarMode == 1) {
                // Mod1 ayar => mod1_digit2++
                mod1_digit2++;
                if (mod1_digit2 >= 10) {
                    mod1_digit2 = 0;
                }
            }
            else if (ayarMode == 2) {
                // Mod2 ayar => mod2_digit2++
                mod2_digit2++;
                if (mod2_digit2 >= 10) {
                    mod2_digit2 = 0;
                }
            }
            else {
                // Normal mod => buton2 => istersek ek bir şey
                // (ama siz normal moddayken buton2'yi basılı tutunca ileri sayma istiyordunuz)
                // Onu application_process içinde kontrol ediyorsunuz.
                // Burada ek bir logic yoksa boş geçilebilir.
            }
        }
    }
    else
    {
        flag &= ~0x04;
    }

    // ---- BUTON3 ----
    if (buton3)
    {
        osDelay(10);
        if ((flag & 0x08) == 0)
        {
            flag |= 0x08;

            if (ayarMode == 1) {
                // Mod1 ayar => BUTON3 => mod1_digit3++
                mod1_digit3++;
                if (mod1_digit3 >= 10) {
                    mod1_digit3 = 0;
                }
            }
            else if (ayarMode == 2) {
                // Mod2 ayar => BUTON3 => mod2_digit3++
                mod2_digit3++;
                if (mod2_digit3 >= 10) {
                    mod2_digit3 = 0;
                }
            }
            else {
                // Normal mod => BUTON3 => Mod2 göster + geri say
                gosterimdekiDeger = 2;
                degerGoster();
                degerSifiraSay();
            }
        }
    }
    else
    {
        flag &= ~0x08;
    }
}

void degerGoster(void)
{
    if (gosterimdekiDeger == 1) {
        // Mod1 (2 hane): digit2-digit3
        digit1 = 0;
        digit2 = mod1_digit2;
        digit3 = mod1_digit3;
    }
    else if (gosterimdekiDeger == 2) {
        // Mod2 (3 hane): digit1-digit2-digit3
        digit1 = mod2_digit1;
        digit2 = mod2_digit2;
        digit3 = mod2_digit3;
    }
}

/**
 * @brief degerSifiraSay
 *        Normal modda Ekrandaki (digit1,digit2,digit3) değerini 0'a kadar geri sayar.
 */
void degerSifiraSay(void)
{
    gerisayimAktif = 1;
    // application_process içinde her 100 ms'de bir azalt.
}

/**
 * @brief application_process
 *        Uygulamamızın ana döngü fonksiyonudur.
 */
void application_process(void)
{
    // 1) Butonları kontrol et
    buton_kontrol();
    //ayarMode = 0;
    // 2) Zaman ilerlet (örnek: 1 ms)
    osDelay(1);
    sayim_timer++;
    ayarMode = 0;
    // 4) AYAR MODU GÖSTERİM (YANIP SÖNME)
    if (ayarMode == 1)
    {
        // Mod1: 2 haneli => digit2, digit3
        if (disp_flasor > 200) disp_flasor = 0;

        if (disp_flasor < 100) {
            // Ekranı boşalt
            display_value[0] = 0x0b;
            display_value[1] = 0x0b;
            display_value[2] = 0x0b;
        }
        else {
            // digit1 sabit 0 göstersin, digit2 & digit3 mod1 değerleri
            display_value[0] = 0;
            display_value[1] = mod1_digit2;
            display_value[2] = mod1_digit3;
        }
    }
    else if (ayarMode == 2)
    {
        // Mod2: 3 haneli => digit1, digit2, digit3
        if (disp_flasor > 200) disp_flasor = 0;

        if (disp_flasor < 100) {
            display_value[0] = 0x0b;
            display_value[1] = 0x0b;
            display_value[2] = 0x0b;
        }
        else {
            display_value[0] = mod2_digit1;
            display_value[1] = mod2_digit2;
            display_value[2] = mod2_digit3;
        }
    }
    else
    {
        // ============ NORMAL MOD ============
        // 5) Geri sayım varsa digit1-digit2-digit3'ü 0'a kadar düşür
        if (gerisayimAktif)
        {
            // Örneğin her 100 ms'de bir azalt
            if (sayim_timer % 10 == 0)
            {
                // "gosterimdekiDeger" 1 ise 2 haneli, 2 ise 3 haneli geri sayacağız.
                if (gosterimdekiDeger == 1)
                {
                    // 2 haneli => digit2-digit3
                    uint8_t value = digit2 * 10 + digit3;
                    if (value > 0) {
                        value--;
                        digit2 = value / 10;
                        digit3 = value % 10;
                    } else {
                        gerisayimAktif = 0;
                    }
                }
                else if (gosterimdekiDeger == 2)
                {
                    // 3 haneli => digit1-digit2-digit3
                    uint16_t value = (digit1 * 100) + (digit2 * 10) + digit3;
                    if (value > 0) {
                        value--;
                        digit1 = value / 100;
                        digit2 = (value / 10) % 10;
                        digit3 = value % 10;
                    } else {
                        gerisayimAktif = 0;
                    }
                }
                else {
                    // Beklenmeyen durum
                    gerisayimAktif = 0;
                }
            }
        }

        // 6) BUTON2 basılı tutma ile manuel artış isteniyorsa (opsiyonel)
        // Burada örnek bir hız (5 ms)
//        if (buton2 && (gerisayimAktif == 0)) {
//            if (sayim_timer % 5 == 0) {
//                digit3++;
//                if (digit3 > 9) {
//                    digit3 = 0;
//                    digit2++;
//                    if (digit2 > 9) {
//                        digit2 = 0;
//                        digit1++;
//                        if (digit1 > 9) {
//                            digit1 = 9;  // 999 sınırı
//                            digit1 = 0;
//                        }
//                    }
//                }
//            }
//        }
    }
//       if(switch1 && (gerisayimAktif == 0)){
//    	   //digit2=0;
//    	  // digit1=0;
//           if (sayim_timer % 17 == 0) {
//               digit3++;
//               if (digit3 > 9) {
//                   digit3 = 0;
//                   digit2++;
//                   if (digit2 > 9) {
//                       digit2 = 0;
//                       digit1++;
//                       if (digit1 > 9) {
//                           digit1 = 9;  // 999 sınırı
//                           digit1 = 0;
//                       }
//                   }
//               }
//           }
//       }

       if (switch1 && (gerisayimAktif == 0))
          {
              // -- A) Yeni basış tespiti --
              if (switch1_previous == false)
              {
                  // Yeni basıldı: Sayaçları sıfırla
                  digit1 = 0;
                  digit2 = 0;
                  digit3 = 0;
              }

              // -- B) Basılı tutulmaya devam ediliyorsa, istenen aralıkta arttırma --
              if (sayim_timer % 17 == 0)
              {
                  digit3++;
                  if (digit3 > 9)
                  {
                      digit3 = 0;
                      digit2++;
                      if (digit2 > 9)
                      {
                          digit2 = 0;
                          digit1++;
                          if (digit1 > 9)
                          {
                              digit1 = 9;  // İsteğe göre 999 sınırı
                          }
                      }
                  }
              }

              // switch1 şu anda basılı, previous değerini true yap
              switch1_previous = true;
          }
          else
          {
              // switch1 basılı değilse, previous değerini false yap
              switch1_previous = false;
          }
        // Ekrana digit1, digit2, digit3'ü göster
        display_value[0] = digit2;
        display_value[1] = digit1;
  //    display_value[2] = digit3;


    // disp_flasor ilerlet
    disp_flasor++;

    // 7) Röle kontrolü
    // Normal modda buton2 basılı tutuyorsanız veya geri sayım aktifse röleyi SET edelim
    if ((buton2 && (gerisayimAktif == 0)) || (switch1 && (gerisayimAktif == 0))) {
        HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
    }
    else {
        HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
    }

    // 8) Display göster
    display_show(display_value);
}
