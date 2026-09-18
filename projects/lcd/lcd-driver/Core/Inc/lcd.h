/*
 * lcd.h
 *
 *  Created on: Jul 6, 2026
 *      Author: nguye
 */

#ifndef __LCD_H
#define __LCD_H

#include "main.h"

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_putc(char c);
void lcd_print(char *str);

#endif
