/*
 * lcd_renderer.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "lcd_renderer.h"
#include "lcd.h"
#include "render.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define CGRAM_SLOT_COUNT    8

typedef struct
{
    uint8_t pattern[FB_BLOCK_H];
    bool used;

} CGRAMSlot_t;

static CGRAMSlot_t cgram_cache[CGRAM_SLOT_COUNT];

/*------------------------------------------------------------------
 * Private Functions
 *-----------------------------------------------------------------*/

/*
 * Tìm pattern trong CGRAM cache.
 *
 * Trả về:
 *  >=0 : Slot đã tồn tại
 *   -1 : Không tìm thấy
 */
static int8_t cgram_find_pattern(const uint8_t pattern[FB_BLOCK_H])
{
    for (uint8_t i = 0; i < CGRAM_SLOT_COUNT; i++)
    {
        if (cgram_cache[i].used &&
            memcmp(pattern,
                   cgram_cache[i].pattern,
                   FB_BLOCK_H) == 0)
        {
            return i;
        }
    }

    return -1;
}

/*
 * Cấp phát slot CGRAM còn trống.
 *
 * Version 1:
 * - Không hỗ trợ replacement.
 *
 * Trả về:
 *  >=0 : Slot được cấp phát
 *   -1 : Hết slot
 */
static int8_t cgram_allocate_slot(const uint8_t pattern[FB_BLOCK_H])
{
    for (uint8_t i = 0; i < CGRAM_SLOT_COUNT; i++)
    {
        if (!cgram_cache[i].used)
        {
            memcpy(cgram_cache[i].pattern,
                   pattern,
                   FB_BLOCK_H);

            cgram_cache[i].used = true;

            return i;
        }
    }

    return -1;
}

/*------------------------------------------------------------------
 * Public Functions
 *-----------------------------------------------------------------*/

void lcd_renderer_init(void)
{
    memset(cgram_cache, 0, sizeof(cgram_cache));
}

void lcd_renderer_update(void)
{
    for (uint8_t row = 0; row < RENDER_BLOCK_ROWS; row++)
    {
        for (uint8_t col = 0; col < RENDER_BLOCK_COLS; col++)
        {
            RenderBlock_t *block = &render_buffer[row][col];

            if (!block->dirty)
            {
                continue;
            }

            int8_t slot = cgram_find_pattern(block->pattern);

            if (slot == -1)
            {
                slot = cgram_allocate_slot(block->pattern);

                if (slot == -1)
                {
                    /*
                     * Version 1:
                     * Chưa hỗ trợ thay thế CGRAM.
                     *
                     * TODO:
                     * Version 2:
                     * Support CGRAM replacement policy.
                     */
                    continue;
                }

                lcd_create_char((uint8_t)slot,
                                block->pattern);
            }

            lcd_set_cursor(row, col);
            lcd_write_char((uint8_t)slot);
            block->dirty = false;
        }
    }
}
