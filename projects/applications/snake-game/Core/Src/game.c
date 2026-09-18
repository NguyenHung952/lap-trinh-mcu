/*
 * game.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "game.h"
#include <stddef.h>
#include "collision.h"
#include "grid.h"
#include "random.h"

#define FOOD_SPAWN_MAX_ATTEMPTS    100U

static bool game_find_random_food_position(const Game_t *game,
                                           uint8_t *food_x,
                                           uint8_t *food_y);

static bool game_find_free_cell(const Game_t *game,
                                uint8_t *food_x,
                                uint8_t *food_y);

static void game_spawn_food(Game_t *game);

static bool game_find_random_food_position(const Game_t *game,
                                           uint8_t *food_x,
                                           uint8_t *food_y)
{
    for (uint16_t attempt = 0;
         attempt < FOOD_SPAWN_MAX_ATTEMPTS;
         attempt++)
    {
        uint8_t x =
            (uint8_t)random_range(0U, GRID_WIDTH - 1U);

        uint8_t y =
            (uint8_t)random_range(0U, GRID_HEIGHT - 1U);

        if (!snake_is_occupied(&game->snake, x, y))
        {
            *food_x = x;
            *food_y = y;

            return true;
        }
    }

    return false;
}

static bool game_find_free_cell(const Game_t *game,
                                uint8_t *food_x,
                                uint8_t *food_y)
{
    for (uint8_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint8_t x = 0; x < GRID_WIDTH; x++)
        {
            if (!snake_is_occupied(&game->snake, x, y))
            {
                *food_x = x;
                *food_y = y;

                return true;
            }
        }
    }

    return false;
}

static void game_spawn_food(Game_t *game)
{
    uint8_t food_x;
    uint8_t food_y;

    bool position_found =
        game_find_random_food_position(game,
                                       &food_x,
                                       &food_y);

    /*
     * Random có thể thử trùng nhiều lần dù vẫn còn ô trống.
     * Vì vậy cần quét toàn bộ grid trước khi kết luận hết chỗ.
     */
    if (!position_found)
    {
        position_found =
            game_find_free_cell(game,
                                &food_x,
                                &food_y);
    }

    if (position_found)
    {
        food_set_position(&game->food,
                          food_x,
                          food_y);
    }
    else
    {
        /*
         * Không còn ô trống nghĩa là rắn đã chiếm toàn bộ
         * không gian mà game cho phép.
         */
        food_hide(&game->food);
        game->game_over = true;
    }
}

void game_init(Game_t *game)
{
    if (game == NULL)
    {
        return;
    }

    snake_init(&game->snake);
    food_init(&game->food);

    game->score = 0U;
    game->game_over = false;

    game_spawn_food(game);
}

void game_update(Game_t *game)
{
    if ((game == NULL) || game->game_over)
    {
        return;
    }

    /*
     * Mỗi lần main gọi game_update(), rắn di chuyển một ô.
     * Khoảng thời gian giữa các lần gọi do TIM1 quyết định.
     */
    snake_move(&game->snake);

    if (collision_wall(&game->snake))
    {
        game->snake.alive = false;
        game->game_over = true;

        return;
    }

    if (snake_check_self_collision(&game->snake))
    {
        game->snake.alive = false;
        game->game_over = true;

        return;
    }

    if (collision_food(&game->snake,
                       &game->food))
    {
        snake_grow(&game->snake);

        game->score++;

        food_hide(&game->food);
        game_spawn_food(game);
    }
}

void game_set_direction(Game_t *game,
                        SnakeDirection_t direction)
{
    if ((game == NULL) || game->game_over)
    {
        return;
    }

    snake_set_direction(&game->snake,
                        direction);
}


bool game_is_over(const Game_t *game)
{
    if (game == NULL)
    {
        return true;
    }

    return !game->snake.alive;
}

bool game_is_completed(const Game_t *game)
{
    if (game == NULL)
    {
        return false;
    }

    return snake_get_length(&game->snake) >= MAX_SNAKE_LENGTH;
}

uint16_t game_get_score(const Game_t *game)
{
    if (game == NULL)
    {
        return 0U;
    }

    return game->score;
}

const Snake_t *game_get_snake(const Game_t *game)
{
    if (game == NULL)
    {
        return NULL;
    }

    return &game->snake;
}

const Food_t *game_get_food(const Game_t *game)
{
    if (game == NULL)
    {
        return NULL;
    }

    return &game->food;
}
