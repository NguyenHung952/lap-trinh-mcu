/*
 * led7seg.h
 *
 *  Created on: Jul 4, 2026
 *      Author: nguye
 */

#ifndef LED7SEG_H
#define LED7SEG_H

#include "main.h"

void DisplayDigit(uint8_t led, uint8_t number);
void SendByte(uint8_t data);
void SendBitLED(uint8_t bit);

void LED_display(uint8_t led1,
                 uint8_t led2,
                 uint8_t led3,
                 uint8_t led4,
                 uint8_t led5);

/* Trong đó 10 là mã "tắt LED" (có thể thêm LedCode[10] là tất cả segment tắt). */
#endif
