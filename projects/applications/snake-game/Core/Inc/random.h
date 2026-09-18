/*
 * random.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef INC_RANDOM_H_
#define INC_RANDOM_H_

#include <stdint.h>

/**
 * @brief Khởi tạo bộ sinh số ngẫu nhiên.
 *
 * @param seed Seed ban đầu.
 *             Nếu seed = 0 sẽ dùng seed mặc định.
 */
void random_init(uint32_t seed);

/**
 * @brief Lấy số ngẫu nhiên tiếp theo.
 *
 * @return Giá trị 16-bit.
 */
uint16_t random_get(void);

/**
 * @brief Sinh số ngẫu nhiên trong khoảng [min, max].
 *
 * @param min Giá trị nhỏ nhất.
 * @param max Giá trị lớn nhất.
 *
 * @return Giá trị trong khoảng [min, max].
 */
uint16_t random_range(uint16_t min,
                      uint16_t max);

#endif
