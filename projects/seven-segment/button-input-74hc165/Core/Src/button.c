/*
 * button.c
 *
 *  Created on: Jul 4, 2026
 *      Author: nguye
 */
#include "main.h"
#include "button.h"

static const uint8_t ButtonMask[4] =
{
	0x01, //SW1
	0x20, //SW2
	0x40, //SW3
	0x80 //SW4
};

uint8_t ReadBit(void)
{
    return HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin);
}


void LoadButton(void)
{
    HAL_GPIO_WritePin(SH_LD_GPIO_Port, SH_LD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SH_LD_GPIO_Port, SH_LD_Pin, GPIO_PIN_SET);
}

void ClockPulse(void)
{
    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);

    for(volatile int i = 0; i < 20; i++);

    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);

    for(volatile int i = 0; i < 20; i++);
}

uint8_t Read74HC165(void)
{
    uint8_t data = 0;

    LoadButton();

    for(int i=0; i<20; i++);

    for(int i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= ReadBit();

        ClockPulse();
    }

    return data;
}

uint8_t ButtonPressed(uint8_t data, uint8_t sw)
{
    return ((data & ButtonMask[sw]) == 0);
}


