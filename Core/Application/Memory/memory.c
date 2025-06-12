/*
 * memory.c
 *
 *  Created on: Feb 2, 2023
 *      Author: alpdade
 */

#include "main.h"
#include "memory.h"
#include "../Application/application.h"
#include "../Application/degiskenler.h"
#include <string.h>
#include <stdio.h>
#include "stm32g0xx_hal.h" // stm32g03

// Örnek adres:
#define MEMORY_BASE_ADDR  0x08007000

static MemoryData_t s_memData;

//----------------------------------------------------------------------------------
// Prototipler
static uint32_t GetPage(uint32_t Address);
static uint32_t Flash_Write_Data_64(uint32_t StartAddress, uint64_t *pData, uint16_t numberOfDoubleWords);
static void     Flash_Read_Data_64 (uint32_t StartAddress, uint64_t *pData, uint16_t numberOfDoubleWords);

//----------------------------------------------------------------------------------
// Sayfayı bulma fonksiyonu (örnek)
static uint32_t GetPage(uint32_t Address)
{
    // STM32G0'da her bir sayfa 2 KB veya 4 KB olabilir (MCU'ya göre).
    // Örneğin 2KB ise FLASH_PAGE_SIZE = 0x800
    // Aşağıdaki mantığı projenizin doğru sayfa boyutuna göre düzenleyin.
    for (int indx = 0; indx < 128; indx++)
    {
        uint32_t pageAddr = 0x08000000 + (FLASH_PAGE_SIZE * indx);
        if ((Address >= pageAddr) && (Address < (pageAddr + FLASH_PAGE_SIZE))) {
            return pageAddr;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------
// 2) 64-Bit (Double Word) Yazma Fonksiyonu
//    -> 'pData' dizisi 'numberOfDoubleWords' eleman içerir. Her eleman 64 bit'tir.
static uint32_t Flash_Write_Data_64(uint32_t StartAddress, uint64_t *pData, uint16_t numberOfDoubleWords)
{
    FLASH_EraseInitTypeDef EraseInitStruct = {0};
    uint32_t PAGEError = 0;

    uint32_t firstPage   = GetPage(StartAddress);
    uint32_t endAddress  = StartAddress + (numberOfDoubleWords * 8);
    uint32_t lastPage    = GetPage(endAddress);

    // Flash kilidini aç
    HAL_FLASH_Unlock();

    // Sayfayı sil
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Page        = (firstPage - 0x08000000) / FLASH_PAGE_SIZE;
    EraseInitStruct.NbPages     = ((lastPage - firstPage) / FLASH_PAGE_SIZE) + 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
        HAL_FLASH_Lock();
        return HAL_FLASH_GetError();
    }

    // Programlama: Her seferinde 64 bit (double word)
    for (int i = 0; i < numberOfDoubleWords; i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, StartAddress, pData[i]) != HAL_OK)
        {
            HAL_FLASH_Lock();
            return HAL_FLASH_GetError();
        }
        StartAddress += 8;  // Bir double word ilerliyoruz
    }

    HAL_FLASH_Lock();
    return 0; // Başarılı
}

//----------------------------------------------------------------------------------
// 3) 64-Bit (Double Word) Okuma Fonksiyonu
static void Flash_Read_Data_64(uint32_t StartAddress, uint64_t *pData, uint16_t numberOfDoubleWords)
{
    for(int i = 0; i < numberOfDoubleWords; i++)
    {
        pData[i] = *(__IO uint64_t*) StartAddress;
        StartAddress += 8;
    }
}

//----------------------------------------------------------------------------------
// 4) Uygulama açılışında (ya da reset sonrası) flash'tan okuyan fonksiyon
void memory_init_values(void)
{
    // Kaç adet double word saklayacağımızı hesapla
    uint16_t dwCount = (sizeof(MemoryData_t) + 7) / 8; // 16/8=2

    // 4A) Flash'tan oku
    memset(&s_memData, 0, sizeof(s_memData));
    Flash_Read_Data_64(MEMORY_BASE_ADDR, (uint64_t*)&s_memData, dwCount);

    // 4B) validFlag kontrol et
    if (s_memData.validFlag != 0xDEADFACE)
    {
        // Default değerler
        s_memData.validFlag   = 0xDEADFACE;
        s_memData.mod1_digit2 = 1;
        s_memData.mod1_digit3 = 2;
        s_memData.mod2_digit1 = 3;
        s_memData.mod2_digit2 = 4;
        s_memData.mod2_digit3 = 5;

        // Flash'a yaz
        Flash_Write_Data_64(MEMORY_BASE_ADDR, (uint64_t*)&s_memData, dwCount);
    }

    // 4C) Global değişkenlere aktar
    mod1_digit2 = s_memData.mod1_digit2;
    mod1_digit3 = s_memData.mod1_digit3;
    mod2_digit1 = s_memData.mod2_digit1;
    mod2_digit2 = s_memData.mod2_digit2;
    mod2_digit3 = s_memData.mod2_digit3;
}

//----------------------------------------------------------------------------------
// 5) Ayar modundan çıkınca kaydeden fonksiyon
void memory_save_values(void)
{
    uint16_t dwCount = (sizeof(MemoryData_t) + 7) / 8;

    // Yapısal verileri güncelle
    s_memData.validFlag   = 0xDEADFACE;
    s_memData.mod1_digit2 = mod1_digit2;
    s_memData.mod1_digit3 = mod1_digit3;
    s_memData.mod2_digit1 = mod2_digit1;
    s_memData.mod2_digit2 = mod2_digit2;
    s_memData.mod2_digit3 = mod2_digit3;

    // Flash'a yaz
    Flash_Write_Data_64(MEMORY_BASE_ADDR, (uint64_t*)&s_memData, dwCount);
}

