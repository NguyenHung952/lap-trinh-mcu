/*
 * timer_adapter.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef TIMER_ADAPTER_H
#define TIMER_ADAPTER_H

#include <stdbool.h>

/**
 * @brief Khởi tạo và chạy TIM1 ở chế độ interrupt.
 *
 * @return true nếu khởi động thành công.
 */
bool timer_adapter_init(void);

/**
 * @brief Báo cho adapter biết TIM1 vừa hết chu kỳ.
 *
 * Hàm này được gọi từ HAL_TIM_PeriodElapsedCallback().
 */
void timer_adapter_tick(void);

/**
 * @brief Kiểm tra có timer tick mới hay không.
 *
 * Nếu có tick, hàm tự động xóa cờ.
 *
 * @return true nếu có tick mới.
 */
bool timer_adapter_poll(void);

#endif /* TIMER_ADAPTER_H */
