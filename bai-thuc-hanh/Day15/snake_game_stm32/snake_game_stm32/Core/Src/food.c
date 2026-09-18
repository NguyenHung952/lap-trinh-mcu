/*
 * food.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "food.h"

void food_init(Food_t *food)
{
    food->x = 0;
    food->y = 0;
    food->active = false;
}

void food_set_position(Food_t *food,
                       uint8_t x,
                       uint8_t y)
{
    food->x = x;
    food->y = y;
    food->active = true;
}

void food_hide(Food_t *food)
{
    food->active = false;
}

bool food_is_active(const Food_t *food)
{
    return food->active;
}
