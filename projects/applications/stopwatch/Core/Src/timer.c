/*
 * timer.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nguye
 */
#include "main.h"
#include "stdbool.h"

extern TIM_HandleTypeDef htim1;
void timer_init(void)
{
    HAL_TIM_Base_Start(&htim1);
}

uint32_t timer_get_tick(void) {
    return __HAL_TIM_GET_COUNTER(&htim1);
}

bool timer_expired(uint32_t *previous_tick,
                   uint32_t interval)
{
    uint32_t now = timer_get_tick();

    if ((now - *previous_tick) >= interval)
    {
        *previous_tick = now;

        return true;
    }

    return false;
}
