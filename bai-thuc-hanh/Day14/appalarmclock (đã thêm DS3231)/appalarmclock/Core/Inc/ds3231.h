#ifndef DS3231_H_
#define DS3231_H_

#include <stdint.h>

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Ds3231Time_t;

void ds3231_init(void);
uint8_t ds3231_is_connected(void);

/*
 * Đọc thời gian từ DS3231.
 *
 * Giá trị trả về:
 *   1U: đọc thành công, dữ liệu hợp lệ
 *   0U: lỗi giao tiếp, con trỏ NULL hoặc dữ liệu không hợp lệ
 */
uint8_t ds3231_read_time(Ds3231Time_t *time);

/*
 * Ghi thời gian vào DS3231 ở chế độ 24 giờ.
 *
 * Giá trị trả về:
 *   1U: ghi thành công
 *   0U: lỗi giao tiếp, con trỏ NULL hoặc thời gian không hợp lệ
 */
uint8_t ds3231_write_time(const Ds3231Time_t *time);

/*
 * Trả nhiệt độ theo đơn vị 0.25 độ C.
 * Ví dụ:
 *   109  -> +27.25 độ C
 *   -5   -> -1.25 độ C
 *
 * Giá trị trả về:
 *   1U: đọc thành công
 *   0U: lỗi giao tiếp hoặc con trỏ NULL
 */
uint8_t ds3231_read_temperature(int16_t *temperature_quarter_c);

#endif /* DS3231_H_ */
