/*
 * snake_renderer.c
 *
 *  Created on: Jul 20, 2026
 *      Author: nguye
 */


#include "snake_renderer.h"

#include <stddef.h>

#include "renderer_utils.h"

void snake_renderer_draw(const Snake_t *snake)
{
    if (snake == NULL)
    {
        return;
    }

    uint8_t length = snake_get_length(snake);

    for (uint8_t i = 0; i < length; i++)
    {
        const SnakeSegment_t *segment =
                snake_get_segment(snake, i);

        if (segment != NULL)
        {
            renderer_draw_cell(segment->x,
                               segment->y,
                               1);
        }
    }
}
