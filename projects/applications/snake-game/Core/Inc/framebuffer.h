#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define FB_WIDTH        80
#define FB_HEIGHT       16

#define FB_BLOCK_W      5
#define FB_BLOCK_H      8

#define FB_BLOCK_COLS   (FB_WIDTH / FB_BLOCK_W)
#define FB_BLOCK_ROWS   (FB_HEIGHT / FB_BLOCK_H)

void fb_init(void);
void fb_clear(void);

void fb_set_pixel(uint8_t x, uint8_t y);
void fb_clear_pixel(uint8_t x, uint8_t y);

bool fb_get_pixel(uint8_t x, uint8_t y);

void fb_get_block(uint8_t block_x,
                  uint8_t block_y,
                  uint8_t pattern[FB_BLOCK_H]);

#endif
