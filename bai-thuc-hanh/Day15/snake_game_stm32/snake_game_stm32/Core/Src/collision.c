/*
 * collision.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "collision.h"
#include "grid.h"

bool collision_wall(const Snake_t *snake)
{
    const SnakeSegment_t *head =
        snake_get_head(snake);

    return !grid_is_valid(head->x, head->y);
}

bool collision_food(const Snake_t *snake,
                    const Food_t *food)
{
    if (!food->active)
    {
        return false;
    }

    const SnakeSegment_t *head =
        snake_get_head(snake);

    return (head->x == food->x) &&
           (head->y == food->y);
}
