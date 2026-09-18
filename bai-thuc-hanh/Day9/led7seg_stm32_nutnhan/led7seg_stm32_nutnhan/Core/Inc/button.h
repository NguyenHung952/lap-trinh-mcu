/*
 * button.h
 *
 *  Created on: Jul 4, 2026
 *      Author: nguye
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

uint8_t Read74HC165(void);
uint8_t ButtonPressed(uint8_t data, uint8_t sw);

#endif
