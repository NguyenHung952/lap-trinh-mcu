/*
 * timer_adapter.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "timer_adapter.h"

#include "main.h"

/*
 * htim1 được định nghĩa trong main.c:
 *
 * TIM_HandleTypeDef htim1;
 */
extern TIM_HandleTypeDef htim1;

static volatile bool timer_flag = false;

bool timer_adapter_init(void)
{
    timer_flag = false;

    if (HAL_TIM_Base_Start_IT(&htim1) != HAL_OK)
    {
        return false;
    }

    return true;
}

void timer_adapter_tick(void)
{
    timer_flag = true;
}

bool timer_adapter_poll(void)
{
    if (!timer_flag)
    {
        return false;
    }

    timer_flag = false;

    return true;
}
