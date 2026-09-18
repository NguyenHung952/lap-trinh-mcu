/*
 * snake.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdint.h>

#include "grid.h"

#define MAX_SNAKE_LENGTH (GRID_WIDTH * GRID_HEIGHT)

typedef enum
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT

} SnakeDirection_t;

typedef struct
{
    uint8_t x;
    uint8_t y;

} SnakeSegment_t;

typedef struct
{
    SnakeSegment_t body[MAX_SNAKE_LENGTH];

    uint8_t length;

    SnakeDirection_t direction;

    bool alive;

} Snake_t;

void snake_init(Snake_t *snake);

void snake_set_direction(Snake_t *snake,
                         SnakeDirection_t direction);

void snake_move(Snake_t *snake);

void snake_grow(Snake_t *snake);

bool snake_check_self_collision(const Snake_t *snake);

bool snake_is_occupied(const Snake_t *snake,
                       uint8_t x,
                       uint8_t y);

/* Getter API */
const SnakeSegment_t *snake_get_head(const Snake_t *snake);

const SnakeSegment_t *snake_get_segment(const Snake_t *snake,
                                        uint8_t index);

uint8_t snake_get_length(const Snake_t *snake);

#endif
