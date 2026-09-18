/*
 * game.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

/*
 * game.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include <stdbool.h>
#include <stdint.h>

#include "food.h"
#include "snake.h"

typedef struct
{
    Snake_t snake;
    Food_t food;

    uint16_t score;
    bool game_over;

} Game_t;

/**
 * @brief Khởi tạo trạng thái trò chơi.
 *
 * @param game Con trỏ tới đối tượng Game_t.
 */
void game_init(Game_t *game);

/**
 * @brief Cập nhật trò chơi một bước.
 *
 * Mỗi lần gọi, rắn sẽ di chuyển đúng một ô, sau đó
 * kiểm tra va chạm và thức ăn.
 *
 * @param game Con trỏ tới đối tượng Game_t.
 */
void game_update(Game_t *game);

/**
 * @brief Yêu cầu thay đổi hướng di chuyển của rắn.
 *
 * @param game      Con trỏ tới đối tượng Game_t.
 * @param direction Hướng di chuyển mới.
 */
void game_set_direction(Game_t *game,
                        SnakeDirection_t direction);

bool game_is_over(const Game_t *game);
bool game_is_completed(const Game_t *game);

uint16_t game_get_score(const Game_t *game);

const Snake_t *game_get_snake(const Game_t *game);

const Food_t *game_get_food(const Game_t *game);

#endif /* INC_GAME_H_ */
