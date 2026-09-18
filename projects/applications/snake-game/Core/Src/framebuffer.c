/*
 * framebuffer.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */
#include "framebuffer.h"
#include <string.h>

static uint8_t framebuffer[FB_HEIGHT][FB_WIDTH];

void fb_init(void)
{
    fb_clear();
}

void fb_clear(void)
{
    memset(framebuffer, 0, sizeof(framebuffer));
}

void fb_set_pixel(uint8_t x, uint8_t y)
{
    if (x >= FB_WIDTH || y >= FB_HEIGHT)
        return;

    framebuffer[y][x] = 1;
}

void fb_clear_pixel(uint8_t x, uint8_t y)
{
    if (x >= FB_WIDTH || y >= FB_HEIGHT)
        return;

    framebuffer[y][x] = 0;
}

bool fb_get_pixel(uint8_t x, uint8_t y)
{
    if (x >= FB_WIDTH || y >= FB_HEIGHT)
        return false;

    return framebuffer[y][x];
}

void fb_get_block(uint8_t block_x,
                  uint8_t block_y,
                  uint8_t pattern[FB_BLOCK_H])
{
    uint8_t start_x = block_x * FB_BLOCK_W;
    uint8_t start_y = block_y * FB_BLOCK_H;

    for (uint8_t row = 0; row < FB_BLOCK_H; row++)
    {
        uint8_t value = 0;

        for (uint8_t col = 0; col < FB_BLOCK_W; col++)
        {
            if (framebuffer[start_y + row][start_x + col])
            {
                value |= (1 << (FB_BLOCK_W - 1 - col));
            }
        }

        pattern[row] = value;
    }
}
