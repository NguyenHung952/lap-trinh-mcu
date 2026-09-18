/*
 * snake.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "snake.h"
#include <stddef.h>
void snake_init(Snake_t *snake)
{
    snake->length = 3;

    snake->body[0] = (SnakeSegment_t){10,2};
    snake->body[1] = (SnakeSegment_t){9,2};
    snake->body[2] = (SnakeSegment_t){8,2};

    snake->direction = DIR_RIGHT;

    snake->alive = true;
}

void snake_set_direction(Snake_t *snake,
                         SnakeDirection_t direction)
{
    if ((snake->direction == DIR_UP    && direction == DIR_DOWN) ||
        (snake->direction == DIR_DOWN  && direction == DIR_UP)   ||
        (snake->direction == DIR_LEFT  && direction == DIR_RIGHT)||
        (snake->direction == DIR_RIGHT && direction == DIR_LEFT))
    {
        return;
    }

    snake->direction = direction;
}

void snake_move(Snake_t *snake)
{
    if (!snake->alive || snake->length == 0)
    {
        return;
    }

    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->direction)
    {
        case DIR_UP:
            snake->body[0].y--;
            break;

        case DIR_DOWN:
            snake->body[0].y++;
            break;

        case DIR_LEFT:
            snake->body[0].x--;
            break;

        case DIR_RIGHT:
            snake->body[0].x++;
            break;
    }
}

void snake_grow(Snake_t *snake)
{
    if (snake->length >= MAX_SNAKE_LENGTH)
    {
        return;
    }

    snake->body[snake->length] =
        snake->body[snake->length - 1];

    snake->length++;
}

bool snake_check_self_collision(const Snake_t *snake)
{
    if (snake->length < 4)
    {
        return false;
    }

    for (uint8_t i = 1; i < snake->length; i++)
    {
        if ((snake->body[0].x == snake->body[i].x) &&
            (snake->body[0].y == snake->body[i].y))
        {
            return true;
        }
    }

    return false;
}

bool snake_is_occupied(const Snake_t *snake,
                       uint8_t x,
                       uint8_t y)
{
    for (uint8_t i = 0; i < snake->length; i++)
    {
        if ((snake->body[i].x == x) &&
            (snake->body[i].y == y))
        {
            return true;
        }
    }

    return false;
}

const SnakeSegment_t *snake_get_head(const Snake_t *snake)
{
    return &snake->body[0];
}

const SnakeSegment_t *snake_get_segment(const Snake_t *snake,
                                        uint8_t index)
{
    if (index >= snake->length)
    {
        return NULL;
    }

    return &snake->body[index];
}

uint8_t snake_get_length(const Snake_t *snake)
{
    return snake->length;
}
