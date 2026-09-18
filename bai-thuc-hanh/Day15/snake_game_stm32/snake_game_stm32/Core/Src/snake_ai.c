/*
 * snake_ai.c
 *
 * Snake AI Level 3:
 * - BFS tìm thức ăn
 * - Virtual Snake kiểm tra đường thoát
 * - Theo đuôi nếu đường ăn không an toàn
 * - Chọn vùng trống lớn nhất khi không còn đường rõ ràng
 */

#include "snake_ai.h"

#include <stddef.h>
#include <string.h>

#include "grid.h"

#define AI_CELL_COUNT       (GRID_WIDTH * GRID_HEIGHT)
#define AI_INVALID_PARENT   (-1)

typedef struct
{
    uint8_t x;
    uint8_t y;
} AiPoint_t;

/* -------------------------------------------------------------------------- */
/* Private function prototypes                                                */
/* -------------------------------------------------------------------------- */

static uint16_t ai_index(uint8_t x, uint8_t y);

static bool ai_is_inside(int16_t x, int16_t y);

static bool ai_is_opposite(SnakeDirection_t current,
                           SnakeDirection_t candidate);

static bool ai_direction_from_points(const AiPoint_t *from,
                                     const AiPoint_t *to,
                                     SnakeDirection_t *direction);

static bool ai_get_next_position(const SnakeSegment_t *head,
                                 SnakeDirection_t direction,
                                 int16_t *next_x,
                                 int16_t *next_y);

static void ai_build_occupied_map(const Snake_t *snake,
                                  bool occupied[AI_CELL_COUNT]);

static bool ai_find_path(const Snake_t *snake,
                         AiPoint_t target,
                         bool allow_target_occupied,
                         AiPoint_t path[AI_CELL_COUNT],
                         uint8_t *path_length);

static bool ai_simulate_path(const Snake_t *snake,
                             const AiPoint_t path[AI_CELL_COUNT],
                             uint8_t path_length,
                             const Food_t *food,
                             Snake_t *virtual_snake);

static bool ai_virtual_snake_can_reach_tail(const Snake_t *snake);

static bool ai_is_immediate_move_safe(const Snake_t *snake,
                                      const Food_t *food,
                                      SnakeDirection_t direction);

static uint8_t ai_count_reachable_space(const Snake_t *snake,
                                        SnakeDirection_t direction);

static bool ai_choose_largest_space(const Snake_t *snake,
                                    const Food_t *food,
                                    SnakeDirection_t *direction);

/* -------------------------------------------------------------------------- */
/* Public API                                                                 */
/* -------------------------------------------------------------------------- */

bool snake_ai_choose_direction(const Snake_t *snake,
                               const Food_t *food,
                               SnakeDirection_t *direction)
{
    if ((snake == NULL) ||
        (food == NULL) ||
        (direction == NULL) ||
        (!snake->alive) ||
        (!food_is_active(food)))
    {
        return false;
    }

    /*
     * BƯỚC 1:
     * BFS tìm đường ngắn nhất từ đầu rắn tới thức ăn.
     */
    AiPoint_t food_path[AI_CELL_COUNT];
    uint8_t food_path_length = 0U;

    AiPoint_t food_target =
    {
        .x = food->x,
        .y = food->y
    };

    bool food_path_found =
        ai_find_path(snake,
                     food_target,
                     false,
                     food_path,
                     &food_path_length);

    /*
     * Một đường hợp lệ phải gồm ít nhất:
     * path[0] = đầu hiện tại
     * path[1] = bước tiếp theo
     */
    if (food_path_found && (food_path_length >= 2U))
    {
        Snake_t virtual_snake;

        /*
         * BƯỚC 2:
         * Cho Virtual Snake đi hết đường và giả lập ăn thức ăn.
         */
        if (ai_simulate_path(snake,
                             food_path,
                             food_path_length,
                             food,
                             &virtual_snake))
        {
            /*
             * BƯỚC 3:
             * Chỉ chấp nhận đường ăn nếu sau khi ăn,
             * đầu rắn vẫn còn đường tiếp cận đuôi.
             */
            if (ai_virtual_snake_can_reach_tail(&virtual_snake))
            {
                SnakeDirection_t food_direction;

                if (ai_direction_from_points(&food_path[0],
                                             &food_path[1],
                                             &food_direction))
                {
                    if (!ai_is_opposite(snake->direction,
                                        food_direction))
                    {
                        *direction = food_direction;
                        return true;
                    }
                }
            }
        }
    }

    /*
     * BƯỚC 4:
     * Đường tới thức ăn không an toàn.
     * Tìm đường tới đuôi để duy trì không gian sống.
     */
    uint8_t snake_length = snake_get_length(snake);

    if (snake_length > 0U)
    {
        const SnakeSegment_t *tail =
            snake_get_segment(snake,
                              (uint8_t)(snake_length - 1U));

        if (tail != NULL)
        {
            AiPoint_t tail_path[AI_CELL_COUNT];
            uint8_t tail_path_length = 0U;

            AiPoint_t tail_target =
            {
                .x = tail->x,
                .y = tail->y
            };

            bool tail_path_found =
                ai_find_path(snake,
                             tail_target,
                             true,
                             tail_path,
                             &tail_path_length);

            if (tail_path_found && (tail_path_length >= 2U))
            {
                SnakeDirection_t tail_direction;

                if (ai_direction_from_points(&tail_path[0],
                                             &tail_path[1],
                                             &tail_direction))
                {
                    if (!ai_is_opposite(snake->direction,
                                        tail_direction) &&
                        ai_is_immediate_move_safe(snake,
                                                  food,
                                                  tail_direction))
                    {
                        *direction = tail_direction;
                        return true;
                    }
                }
            }
        }
    }

    /*
     * BƯỚC 5:
     * Không có đường rõ ràng tới thức ăn hoặc đuôi.
     * Chọn bước dẫn tới vùng trống lớn nhất.
     */
    return ai_choose_largest_space(snake,
                                   food,
                                   direction);
}

/* -------------------------------------------------------------------------- */
/* BFS                                                                        */
/* -------------------------------------------------------------------------- */

static bool ai_find_path(const Snake_t *snake,
                         AiPoint_t target,
                         bool allow_target_occupied,
                         AiPoint_t path[AI_CELL_COUNT],
                         uint8_t *path_length)
{
    if ((snake == NULL) ||
        (path == NULL) ||
        (path_length == NULL))
    {
        return false;
    }

    const SnakeSegment_t *head = snake_get_head(snake);

    if (head == NULL)
    {
        return false;
    }

    bool occupied[AI_CELL_COUNT];
    bool visited[AI_CELL_COUNT];

    int16_t parent[AI_CELL_COUNT];

    uint16_t queue[AI_CELL_COUNT];
    uint8_t queue_front = 0U;
    uint8_t queue_back = 0U;

    ai_build_occupied_map(snake, occupied);

    memset(visited, 0, sizeof(visited));

    for (uint16_t i = 0U; i < AI_CELL_COUNT; i++)
    {
        parent[i] = AI_INVALID_PARENT;
    }

    uint16_t start_index =
        ai_index(head->x, head->y);

    uint16_t target_index =
        ai_index(target.x, target.y);

    /*
     * Đầu rắn là điểm bắt đầu nên không được coi là vật cản.
     */
    occupied[start_index] = false;

    /*
     * Khi tìm đường tới đuôi, vị trí đuôi được phép là đích
     * dù hiện tại đang thuộc thân rắn.
     */
    if (allow_target_occupied)
    {
        occupied[target_index] = false;
    }

    queue[queue_back++] = start_index;
    visited[start_index] = true;

    static const int8_t dx[4] = {0, 0, -1, 1};
    static const int8_t dy[4] = {-1, 1, 0, 0};

    bool found = false;

    while (queue_front < queue_back)
    {
        uint16_t current_index =
            queue[queue_front++];

        if (current_index == target_index)
        {
            found = true;
            break;
        }

        uint8_t current_x =
            (uint8_t)(current_index % GRID_WIDTH);

        uint8_t current_y =
            (uint8_t)(current_index / GRID_WIDTH);

        for (uint8_t i = 0U; i < 4U; i++)
        {
            int16_t next_x =
                (int16_t)current_x + dx[i];

            int16_t next_y =
                (int16_t)current_y + dy[i];

            if (!ai_is_inside(next_x, next_y))
            {
                continue;
            }

            uint16_t next_index =
                ai_index((uint8_t)next_x,
                         (uint8_t)next_y);

            if (visited[next_index] ||
                occupied[next_index])
            {
                continue;
            }

            /*
             * Ở bước đầu tiên, không cho AI quay ngược trực tiếp.
             */
            if (current_index == start_index)
            {
                AiPoint_t from =
                {
                    .x = head->x,
                    .y = head->y
                };

                AiPoint_t to =
                {
                    .x = (uint8_t)next_x,
                    .y = (uint8_t)next_y
                };

                SnakeDirection_t first_direction;

                if (ai_direction_from_points(&from,
                                             &to,
                                             &first_direction))
                {
                    if (ai_is_opposite(snake->direction,
                                       first_direction))
                    {
                        continue;
                    }
                }
            }

            visited[next_index] = true;
            parent[next_index] = (int16_t)current_index;

            if (queue_back < AI_CELL_COUNT)
            {
                queue[queue_back++] = next_index;
            }
        }
    }

    if (!found)
    {
        *path_length = 0U;
        return false;
    }

    /*
     * Truy ngược từ đích về đầu.
     */
    uint16_t reverse_path[AI_CELL_COUNT];
    uint8_t reverse_length = 0U;

    int16_t current = (int16_t)target_index;

    while ((current >= 0) &&
           (reverse_length < AI_CELL_COUNT))
    {
        reverse_path[reverse_length++] =
            (uint16_t)current;

        if ((uint16_t)current == start_index)
        {
            break;
        }

        current = parent[current];
    }

    if ((reverse_length == 0U) ||
        (reverse_path[reverse_length - 1U] != start_index))
    {
        *path_length = 0U;
        return false;
    }

    /*
     * Đảo lại thành:
     * đầu hiện tại → ... → đích.
     */
    for (uint8_t i = 0U; i < reverse_length; i++)
    {
        uint16_t index =
            reverse_path[reverse_length - 1U - i];

        path[i].x =
            (uint8_t)(index % GRID_WIDTH);

        path[i].y =
            (uint8_t)(index / GRID_WIDTH);
    }

    *path_length = reverse_length;

    return true;
}

/* -------------------------------------------------------------------------- */
/* Virtual Snake                                                              */
/* -------------------------------------------------------------------------- */

static bool ai_simulate_path(const Snake_t *snake,
                             const AiPoint_t path[AI_CELL_COUNT],
                             uint8_t path_length,
                             const Food_t *food,
                             Snake_t *virtual_snake)
{
    if ((snake == NULL) ||
        (path == NULL) ||
        (food == NULL) ||
        (virtual_snake == NULL) ||
        (path_length < 2U))
    {
        return false;
    }

    /*
     * Sao chép toàn bộ trạng thái rắn thật.
     */
    *virtual_snake = *snake;

    for (uint8_t i = 1U; i < path_length; i++)
    {
        const SnakeSegment_t *virtual_head =
            snake_get_head(virtual_snake);

        if (virtual_head == NULL)
        {
            return false;
        }

        AiPoint_t current =
        {
            .x = virtual_head->x,
            .y = virtual_head->y
        };

        SnakeDirection_t next_direction;

        if (!ai_direction_from_points(&current,
                                      &path[i],
                                      &next_direction))
        {
            return false;
        }

        snake_set_direction(virtual_snake,
                            next_direction);

        snake_move(virtual_snake);

        const SnakeSegment_t *new_head =
            snake_get_head(virtual_snake);

        if (new_head == NULL)
        {
            return false;
        }

        if (!grid_is_valid(new_head->x,
                           new_head->y))
        {
            return false;
        }

        if (snake_check_self_collision(virtual_snake))
        {
            return false;
        }
    }

    const SnakeSegment_t *final_head =
        snake_get_head(virtual_snake);

    if (final_head == NULL)
    {
        return false;
    }

    /*
     * Nếu Virtual Snake đã tới thức ăn thì tăng chiều dài,
     * tương tự game_update().
     */
    if ((final_head->x == food->x) &&
        (final_head->y == food->y))
    {
        snake_grow(virtual_snake);
    }

    return true;
}

static bool ai_virtual_snake_can_reach_tail(const Snake_t *snake)
{
    if (snake == NULL)
    {
        return false;
    }

    uint8_t length = snake_get_length(snake);

    if (length == 0U)
    {
        return false;
    }

    const SnakeSegment_t *tail =
        snake_get_segment(snake,
                          (uint8_t)(length - 1U));

    if (tail == NULL)
    {
        return false;
    }

    AiPoint_t tail_target =
    {
        .x = tail->x,
        .y = tail->y
    };

    AiPoint_t path[AI_CELL_COUNT];
    uint8_t path_length = 0U;

    return ai_find_path(snake,
                        tail_target,
                        true,
                        path,
                        &path_length);
}

/* -------------------------------------------------------------------------- */
/* Fallback safety                                                            */
/* -------------------------------------------------------------------------- */

static bool ai_choose_largest_space(const Snake_t *snake,
                                    const Food_t *food,
                                    SnakeDirection_t *direction)
{
    static const SnakeDirection_t directions[4] =
    {
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };

    bool found = false;
    uint8_t best_space = 0U;
    SnakeDirection_t best_direction =
        snake->direction;

    for (uint8_t i = 0U; i < 4U; i++)
    {
        SnakeDirection_t candidate =
            directions[i];

        if (ai_is_opposite(snake->direction,
                           candidate))
        {
            continue;
        }

        if (!ai_is_immediate_move_safe(snake,
                                       food,
                                       candidate))
        {
            continue;
        }

        uint8_t reachable_space =
            ai_count_reachable_space(snake,
                                     candidate);

        if ((!found) ||
            (reachable_space > best_space))
        {
            found = true;
            best_space = reachable_space;
            best_direction = candidate;
        }
    }

    if (found)
    {
        *direction = best_direction;
        return true;
    }

    return false;
}

static uint8_t ai_count_reachable_space(const Snake_t *snake,
                                        SnakeDirection_t direction)
{
    const SnakeSegment_t *head =
        snake_get_head(snake);

    if (head == NULL)
    {
        return 0U;
    }

    int16_t start_x;
    int16_t start_y;

    if (!ai_get_next_position(head,
                              direction,
                              &start_x,
                              &start_y))
    {
        return 0U;
    }

    if (!ai_is_inside(start_x, start_y))
    {
        return 0U;
    }

    bool occupied[AI_CELL_COUNT];
    bool visited[AI_CELL_COUNT];

    uint16_t queue[AI_CELL_COUNT];
    uint8_t queue_front = 0U;
    uint8_t queue_back = 0U;

    ai_build_occupied_map(snake,
                          occupied);

    memset(visited, 0, sizeof(visited));

    uint16_t start_index =
        ai_index((uint8_t)start_x,
                 (uint8_t)start_y);

    /*
     * Cho phép bước vào vị trí đuôi vì đuôi có thể rời đi
     * sau một bước nếu không ăn thức ăn.
     */
    uint8_t length = snake_get_length(snake);

    if (length > 0U)
    {
        const SnakeSegment_t *tail =
            snake_get_segment(snake,
                              (uint8_t)(length - 1U));

        if (tail != NULL)
        {
            occupied[ai_index(tail->x,
                              tail->y)] = false;
        }
    }

    occupied[start_index] = false;

    queue[queue_back++] = start_index;
    visited[start_index] = true;

    uint8_t reachable_count = 0U;

    static const int8_t dx[4] = {0, 0, -1, 1};
    static const int8_t dy[4] = {-1, 1, 0, 0};

    while (queue_front < queue_back)
    {
        uint16_t current_index =
            queue[queue_front++];

        reachable_count++;

        uint8_t current_x =
            (uint8_t)(current_index % GRID_WIDTH);

        uint8_t current_y =
            (uint8_t)(current_index / GRID_WIDTH);

        for (uint8_t i = 0U; i < 4U; i++)
        {
            int16_t next_x =
                (int16_t)current_x + dx[i];

            int16_t next_y =
                (int16_t)current_y + dy[i];

            if (!ai_is_inside(next_x, next_y))
            {
                continue;
            }

            uint16_t next_index =
                ai_index((uint8_t)next_x,
                         (uint8_t)next_y);

            if (visited[next_index] ||
                occupied[next_index])
            {
                continue;
            }

            visited[next_index] = true;

            if (queue_back < AI_CELL_COUNT)
            {
                queue[queue_back++] = next_index;
            }
        }
    }

    return reachable_count;
}

static bool ai_is_immediate_move_safe(const Snake_t *snake,
                                      const Food_t *food,
                                      SnakeDirection_t direction)
{
    const SnakeSegment_t *head =
        snake_get_head(snake);

    if ((head == NULL) ||
        (food == NULL))
    {
        return false;
    }

    int16_t next_x;
    int16_t next_y;

    if (!ai_get_next_position(head,
                              direction,
                              &next_x,
                              &next_y))
    {
        return false;
    }

    if (!ai_is_inside(next_x, next_y))
    {
        return false;
    }

    uint8_t next_x_u8 = (uint8_t)next_x;
    uint8_t next_y_u8 = (uint8_t)next_y;

    if (!snake_is_occupied(snake,
                           next_x_u8,
                           next_y_u8))
    {
        return true;
    }

    /*
     * Có thể đi vào ô đuôi nếu:
     * - ô đó đúng là đuôi hiện tại;
     * - bước này không ăn thức ăn;
     * vì đuôi sẽ dịch chuyển khỏi ô đó.
     */
    uint8_t length = snake_get_length(snake);

    if (length == 0U)
    {
        return false;
    }

    const SnakeSegment_t *tail =
        snake_get_segment(snake,
                          (uint8_t)(length - 1U));

    if (tail == NULL)
    {
        return false;
    }

    bool moving_into_tail =
        ((tail->x == next_x_u8) &&
         (tail->y == next_y_u8));

    bool eating_food =
        ((food->x == next_x_u8) &&
         (food->y == next_y_u8));

    return moving_into_tail && !eating_food;
}

/* -------------------------------------------------------------------------- */
/* Utility                                                                    */
/* -------------------------------------------------------------------------- */

static uint16_t ai_index(uint8_t x, uint8_t y)
{
    return (uint16_t)y * GRID_WIDTH + x;
}

static bool ai_is_inside(int16_t x, int16_t y)
{
    return
        (x >= 0) &&
        (x < GRID_WIDTH) &&
        (y >= 0) &&
        (y < GRID_HEIGHT);
}

static bool ai_is_opposite(SnakeDirection_t current,
                           SnakeDirection_t candidate)
{
    return
        ((current == DIR_UP) &&
         (candidate == DIR_DOWN)) ||

        ((current == DIR_DOWN) &&
         (candidate == DIR_UP)) ||

        ((current == DIR_LEFT) &&
         (candidate == DIR_RIGHT)) ||

        ((current == DIR_RIGHT) &&
         (candidate == DIR_LEFT));
}

static bool ai_direction_from_points(const AiPoint_t *from,
                                     const AiPoint_t *to,
                                     SnakeDirection_t *direction)
{
    if ((from == NULL) ||
        (to == NULL) ||
        (direction == NULL))
    {
        return false;
    }

    if ((to->x == (uint8_t)(from->x + 1U)) &&
        (to->y == from->y))
    {
        *direction = DIR_RIGHT;
        return true;
    }

    if (((uint16_t)to->x + 1U == from->x) &&
        (to->y == from->y))
    {
        *direction = DIR_LEFT;
        return true;
    }

    if ((to->y == (uint8_t)(from->y + 1U)) &&
        (to->x == from->x))
    {
        *direction = DIR_DOWN;
        return true;
    }

    if (((uint16_t)to->y + 1U == from->y) &&
        (to->x == from->x))
    {
        *direction = DIR_UP;
        return true;
    }

    return false;
}

static bool ai_get_next_position(const SnakeSegment_t *head,
                                 SnakeDirection_t direction,
                                 int16_t *next_x,
                                 int16_t *next_y)
{
    if ((head == NULL) ||
        (next_x == NULL) ||
        (next_y == NULL))
    {
        return false;
    }

    *next_x = head->x;
    *next_y = head->y;

    switch (direction)
    {
        case DIR_UP:
            (*next_y)--;
            break;

        case DIR_DOWN:
            (*next_y)++;
            break;

        case DIR_LEFT:
            (*next_x)--;
            break;

        case DIR_RIGHT:
            (*next_x)++;
            break;

        default:
            return false;
    }

    return true;
}

static void ai_build_occupied_map(const Snake_t *snake,
                                  bool occupied[AI_CELL_COUNT])
{
    memset(occupied,
           0,
           sizeof(bool) * AI_CELL_COUNT);

    uint8_t length =
        snake_get_length(snake);

    for (uint8_t i = 0U; i < length; i++)
    {
        const SnakeSegment_t *segment =
            snake_get_segment(snake, i);

        if ((segment != NULL) &&
            grid_is_valid(segment->x,
                          segment->y))
        {
            occupied[ai_index(segment->x,
                              segment->y)] = true;
        }
    }
}
