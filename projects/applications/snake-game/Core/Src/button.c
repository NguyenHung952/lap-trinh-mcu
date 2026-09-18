/*
 * button.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */


#include "main.h"
#include "button.h"

#define BUTTON_COUNT 4

static const uint8_t ButtonMask[BUTTON_COUNT] =
{
    0x01,
    0x20,
    0x40,
    0x80
};

uint8_t button_read_bit(void)
{
    uint8_t bit = HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin);

    return bit;
}


void button_load_parallel(void)
{
    HAL_GPIO_WritePin(SH_LD_GPIO_Port, SH_LD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SH_LD_GPIO_Port, SH_LD_Pin, GPIO_PIN_SET);
}

void button_clock_pulse(void)
{
    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);

    for(volatile int i = 0; i < 20; i++);

    HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);

    for(volatile int i = 0; i < 20; i++);
}

uint8_t Read74HC165(void)
{
    uint8_t data = 0;

    button_load_parallel();

    for(int i=0; i<20; i++);

    for(int i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= button_read_bit();

        button_clock_pulse();
    }

    return data;
}

uint8_t ButtonPressed(uint8_t data, uint8_t sw)
{
    return ((data & ButtonMask[sw]) == 0);
}



