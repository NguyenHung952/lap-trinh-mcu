/*
 * food.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t x;
    uint8_t y;

    bool active;

} Food_t;

void food_init(Food_t *food);

void food_set_position(Food_t *food,
                       uint8_t x,
                       uint8_t y);

void food_hide(Food_t *food);

bool food_is_active(const Food_t *food);

#endif
