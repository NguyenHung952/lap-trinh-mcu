/*
 * collision.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "food.h"
#include "snake.h"

bool collision_wall(const Snake_t *snake);

bool collision_food(const Snake_t *snake,
                    const Food_t *food);

#endif
