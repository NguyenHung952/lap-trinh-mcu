/*
 * lcd.h
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#ifndef __LCD_H
#define __LCD_H

#include "main.h"

void lcd_init(void);
void lcd_clear(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_putc(char c);
void lcd_print(const char *str);

/*
 * Tạo ký tự tùy chỉnh trong CGRAM.
 *
 * location: vị trí từ 0 đến 7.
 * pattern : mảng 8 byte, mỗi byte biểu diễn một hàng 5 pixel.
 */
void lcd_create_char(uint8_t location,
                     const uint8_t pattern[8]);

/*
 * Ghi mã ký tự trực tiếp vào DDRAM.
 * Dùng để hiển thị ký tự CGRAM từ 0 đến 7.
 */
void lcd_write_char(uint8_t char_code);

void lcd_display_on(void);
void lcd_display_off(void);

void lcd_cursor_on(void);
void lcd_cursor_off(void);

void lcd_blink_on(void);
void lcd_blink_off(void);

#endif /* __LCD_H */
