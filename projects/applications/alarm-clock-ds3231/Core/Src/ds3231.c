#include "ds3231.h"
#include "soft_i2c.h"

#define DS3231_ADDRESS_7BIT        0x68U
#define DS3231_ADDRESS_WRITE       (DS3231_ADDRESS_7BIT << 1)
#define DS3231_ADDRESS_READ        ((DS3231_ADDRESS_7BIT << 1) | 0x01U)

#define DS3231_SECONDS_REGISTER    0x00U
#define DS3231_TEMP_MSB_REGISTER   0x11U

static uint8_t ds3231_read_registers(uint8_t register_address,
                                     uint8_t *data,
                                     uint8_t size);

static uint8_t ds3231_write_registers(uint8_t register_address,
                                      const uint8_t *data,
                                      uint8_t size);

static uint8_t ds3231_bcd_to_decimal(uint8_t bcd);
static uint8_t ds3231_decimal_to_bcd(uint8_t decimal);

static uint8_t ds3231_read_registers(uint8_t register_address,
                                     uint8_t *data,
                                     uint8_t size)
{
    uint8_t index;

    if((data == 0) || (size == 0U))
    {
        return 0U;
    }

    soft_i2c_start();

    if(soft_i2c_write_byte(DS3231_ADDRESS_WRITE) == 0U)
    {
        soft_i2c_stop();
        return 0U;
    }

    if(soft_i2c_write_byte(register_address) == 0U)
    {
        soft_i2c_stop();
        return 0U;
    }

    soft_i2c_start();

    if(soft_i2c_write_byte(DS3231_ADDRESS_READ) == 0U)
    {
        soft_i2c_stop();
        return 0U;
    }

    for(index = 0U; index < size; index++)
    {
        data[index] =
            soft_i2c_read_byte((index + 1U) < size);
    }

    soft_i2c_stop();
    return 1U;
}

static uint8_t ds3231_write_registers(uint8_t register_address,
                                      const uint8_t *data,
                                      uint8_t size)
{
    uint8_t index;

    if((data == 0) || (size == 0U))
    {
        return 0U;
    }

    soft_i2c_start();

    if(soft_i2c_write_byte(DS3231_ADDRESS_WRITE) == 0U)
    {
        soft_i2c_stop();
        return 0U;
    }

    if(soft_i2c_write_byte(register_address) == 0U)
    {
        soft_i2c_stop();
        return 0U;
    }

    for(index = 0U; index < size; index++)
    {
        if(soft_i2c_write_byte(data[index]) == 0U)
        {
            soft_i2c_stop();
            return 0U;
        }
    }

    soft_i2c_stop();
    return 1U;
}

static uint8_t ds3231_bcd_to_decimal(uint8_t bcd)
{
    return (uint8_t)(((bcd >> 4) * 10U) + (bcd & 0x0FU));
}

static uint8_t ds3231_decimal_to_bcd(uint8_t decimal)
{
    return (uint8_t)(((decimal / 10U) << 4) |
                     (decimal % 10U));
}

void ds3231_init(void)
{
    soft_i2c_init();
}

uint8_t ds3231_is_connected(void)
{
    uint8_t connected;

    soft_i2c_start();
    connected = soft_i2c_write_byte(DS3231_ADDRESS_WRITE);
    soft_i2c_stop();

    return connected;
}

uint8_t ds3231_read_time(Ds3231Time_t *time)
{
    uint8_t data[3];
    uint8_t hour_register;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    if(time == 0)
    {
        return 0U;
    }

    if(ds3231_read_registers(DS3231_SECONDS_REGISTER,
                             data,
                             3U) == 0U)
    {
        return 0U;
    }

    second = ds3231_bcd_to_decimal(data[0] & 0x7FU);
    minute = ds3231_bcd_to_decimal(data[1] & 0x7FU);
    hour_register = data[2];

    /*
     * Bit 6 của thanh ghi giờ:
     *   0: chế độ 24 giờ
     *   1: chế độ 12 giờ
     */
    if((hour_register & 0x40U) == 0U)
    {
        hour = ds3231_bcd_to_decimal(hour_register & 0x3FU);
    }
    else
    {
        uint8_t hour_12;
        uint8_t is_pm;

        hour_12 =
            ds3231_bcd_to_decimal(hour_register & 0x1FU);

        is_pm = (hour_register & 0x20U) != 0U;

        if(hour_12 == 12U)
        {
            hour = (is_pm != 0U) ? 12U : 0U;
        }
        else
        {
            hour = (is_pm != 0U) ?
                   (uint8_t)(hour_12 + 12U) :
                   hour_12;
        }
    }

    if((second >= 60U) ||
       (minute >= 60U) ||
       (hour >= 24U))
    {
        return 0U;
    }

    time->hour = hour;
    time->minute = minute;
    time->second = second;

    return 1U;
}

uint8_t ds3231_write_time(const Ds3231Time_t *time)
{
    uint8_t data[3];

    if(time == 0)
    {
        return 0U;
    }

    if((time->second >= 60U) ||
       (time->minute >= 60U) ||
       (time->hour >= 24U))
    {
        return 0U;
    }

    data[0] = ds3231_decimal_to_bcd(time->second);
    data[1] = ds3231_decimal_to_bcd(time->minute);

    /*
     * Ghi giờ ở chế độ 24 giờ nên bit 6 luôn bằng 0.
     */
    data[2] = ds3231_decimal_to_bcd(time->hour);

    return ds3231_write_registers(DS3231_SECONDS_REGISTER,
                                  data,
                                  3U);
}

uint8_t ds3231_read_temperature(int16_t *temperature_quarter_c)
{
    uint8_t data[2];
    uint16_t raw_10bit;

    if(temperature_quarter_c == 0)
    {
        return 0U;
    }

    if(ds3231_read_registers(DS3231_TEMP_MSB_REGISTER,
                             data,
                             2U) == 0U)
    {
        return 0U;
    }

    /*
     * Thanh ghi 0x11 và 0x12 tạo thành số bù 2 có dấu 10-bit.
     * Mỗi đơn vị sau khi dịch phải 6 bit tương ứng 0.25 độ C.
     */
    raw_10bit =
        (((uint16_t)data[0] << 8) | data[1]) >> 6;

    if((raw_10bit & 0x0200U) != 0U)
    {
        *temperature_quarter_c =
            (int16_t)raw_10bit - 1024;
    }
    else
    {
        *temperature_quarter_c = (int16_t)raw_10bit;
    }

    return 1U;
}
