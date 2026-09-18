/*
 * renderer_utils.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "renderer_utils.h"
#include "framebuffer.h"

void renderer_draw_cell(uint8_t cell_x,
                        uint8_t cell_y,
                        uint8_t color)
{
    uint8_t px = cell_x * RENDER_CELL_SIZE;
    uint8_t py = cell_y * RENDER_CELL_SIZE;

    for (uint8_t dy = 0; dy < RENDER_CELL_SIZE; dy++)
    {
        for (uint8_t dx = 0; dx < RENDER_CELL_SIZE; dx++)
        {
            if (color)
            {
                fb_set_pixel(px + dx, py + dy);
            }
            else
            {
                fb_clear_pixel(px + dx, py + dy);
            }
        }
    }
}
