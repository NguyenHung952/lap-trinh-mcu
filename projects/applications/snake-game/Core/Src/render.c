/*
 * render.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */


#include "render.h"

#include <string.h>

RenderBlock_t render_buffer[RENDER_BLOCK_ROWS][RENDER_BLOCK_COLS];

void render_init(void)
{
    for (uint8_t by = 0; by < RENDER_BLOCK_ROWS; by++)
    {
        for (uint8_t bx = 0; bx < RENDER_BLOCK_COLS; bx++)
        {
            RenderBlock_t *block = &render_buffer[by][bx];

            memset(block->pattern, 0, FB_BLOCK_H);

            /*
             * Sau khi khởi động LCD chưa biết trạng thái thực tế,
             * vì vậy buộc LCD Renderer phải cập nhật toàn bộ.
             */
            block->dirty = true;
        }
    }
}

void render_update(void)
{
    for (uint8_t by = 0; by < RENDER_BLOCK_ROWS; by++)
    {
        for (uint8_t bx = 0; bx < RENDER_BLOCK_COLS; bx++)
        {
            RenderBlock_t *block = &render_buffer[by][bx];

            uint8_t new_pattern[FB_BLOCK_H];

            fb_get_block(bx, by, new_pattern);

            if (memcmp(new_pattern,
                       block->pattern,
                       FB_BLOCK_H) != 0)
            {
                memcpy(block->pattern,
                       new_pattern,
                       FB_BLOCK_H);

                /*
                 * Chỉ Render được phép set dirty = true.
                 * LCD Renderer sẽ clear dirty sau khi đồng bộ LCD.
                 */
                block->dirty = true;
            }
        }
    }


}
