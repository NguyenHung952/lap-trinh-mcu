/*
 * snake_ai.h
 *
 *  Created on: Jul 20, 2026
 *      Author: nguye
 */

#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include <stdbool.h>

#include "food.h"
#include "snake.h"

bool snake_ai_choose_direction(const Snake_t *snake,
                               const Food_t *food,
                               SnakeDirection_t *direction);

#endif
