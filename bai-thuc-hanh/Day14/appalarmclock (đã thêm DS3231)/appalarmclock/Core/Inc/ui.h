/*
 * ui.h
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#ifndef UI_H_
#define UI_H_

#include <stdint.h>
#include "clock.h"
#include "menu.h"

/*==============================*/
/* Public API                   */
/*==============================*/

void ui_init(void);

void ui_update(void);

/*
 * Cập nhật nhiệt độ cho giao diện.
 *
 * temperature_quarter_c:
 *   Nhiệt độ theo đơn vị 0.25 độ C.
 *   Ví dụ:
 *     136  -> 34.00 độ C
 *     137  -> 34.25 độ C
 *
 * temperature_valid:
 *   1U -> nhiệt độ hợp lệ
 *   0U -> lỗi giao tiếp DS3231
 */
void ui_set_temperature(int16_t temperature_quarter_c,
                        uint8_t temperature_valid);

#endif /* UI_H_ */
