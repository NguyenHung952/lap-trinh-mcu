/*
 * led7seg.c
 *
 *  Created on: Jul 4, 2026
 *      Author: nguye
 */
#include <stdint.h>
#include "main.h"
#include "led7seg.h"
extern TIM_HandleTypeDef htim1;
/*-------------------------------------------------
 * LED SELECT
 * CHON LED HIEN THI
 * Index:
 * [0] -> LED1
 * [1] -> LED2
 * [2] -> LED3
 * [3] -> LED4
 * [4] -> LED5
 *------------------------------------------------*/
const uint8_t LedSelect[5] =
{
    0x08,   // LED1
    0x10,   // LED2
    0x20,   // LED3
    0x40,   // LED4
    0x80    // LED5
};

/*-------------------------------------------------
 * SEGMENT DATA (ARM KIT)
 * THU TU BIT:
 *
 * Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
 *   c    g    b   dp    d    e    a    f
 *
 *------------------------------------------------*/
const uint8_t LedCode[10] =
{
    0xAF,   // 0
    0xA0,   // 1
    0x6E,   // 2
    0xEA,   // 3
    0xE1,   // 4
    0xCB,   // 5
    0xCF,   // 6
    0xA2,   // 7
    0xEF,   // 8
    0xEB    // 9
};


void SendBitLED(uint8_t bit)
{
    if(bit)
        HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
}

void SendByte(uint8_t data)
{

    for(int i = 7; i >= 0; i--)
    {
        SendBitLED((data >> i) & 0x01);
    }
}
void KhoidongLED(void)
{
    /* Enable 74HC595 (/OE = 0) */
    HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);

    /* SET UP TRANG THAI BAN DAU */
    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST_CP_GPIO_Port, ST_CP_Pin, GPIO_PIN_RESET);

}

void Ketthuc(void)
{
    /* ==========================================================
       CHOT DU LIEU RA OUTPUT
       ========================================================== */
    HAL_GPIO_WritePin(ST_CP_GPIO_Port, ST_CP_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ST_CP_GPIO_Port, ST_CP_Pin, GPIO_PIN_RESET);

}


void DisplayDigit(uint8_t led, uint8_t number)
{
    KhoidongLED();

    SendByte(LedSelect[led]);

    SendByte(LedCode[number]);

    Ketthuc();
}

void LED_display(uint8_t led1,
                 uint8_t led2,
                 uint8_t led3,
                 uint8_t led4,
                 uint8_t led5)
{
    DisplayDigit(0,led1);
    HAL_Delay(50);

    DisplayDigit(1,led2);
    HAL_Delay(50);

    DisplayDigit(2,led3);
    HAL_Delay(50);

    DisplayDigit(3,led4);
    HAL_Delay(50);

    DisplayDigit(4,led5);
    HAL_Delay(50);
}

