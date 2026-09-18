/*
 * food_renderer.c
 *
 *  Created on: Jul 20, 2026
 *      Author: nguye
 */


#include "food_renderer.h"

#include <stddef.h>

#include "renderer_utils.h"

void food_renderer_draw(const Food_t *food)
{
    if (food == NULL)
    {
        return;
    }

    if (!food_is_active(food))
    {
        return;
    }

    renderer_draw_cell(food->x,
                       food->y,
                       1);
}
