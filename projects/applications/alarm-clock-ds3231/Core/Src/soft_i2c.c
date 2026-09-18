#include "soft_i2c.h"
#include "main.h"

static void soft_i2c_delay(void)
{
    volatile uint32_t count;

    for (count = 0U; count < 20U; count++)
    {
        __NOP();
    }
}

static void sda_high(void)
{
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
}

static void sda_low(void)
{
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
}

static void scl_high(void)
{
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

static void scl_low(void)
{
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);
}

static uint8_t sda_read(void)
{
    return (HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) == GPIO_PIN_SET) ? 1U : 0U;
}

void soft_i2c_init(void)
{
    uint8_t pulse;

    sda_high();
    scl_high();
    soft_i2c_delay();

    /* Phát tối đa 9 xung SCL nếu SDA đang bị giữ LOW. */
    if (sda_read() == 0U)
    {
        for (pulse = 0U; pulse < 9U; pulse++)
        {
            scl_low();
            soft_i2c_delay();
            scl_high();
            soft_i2c_delay();
        }
    }

    soft_i2c_stop();
}

void soft_i2c_start(void)
{
    sda_high();
    scl_high();
    soft_i2c_delay();
    sda_low();
    soft_i2c_delay();
    scl_low();
}

void soft_i2c_stop(void)
{
    sda_low();
    soft_i2c_delay();
    scl_high();
    soft_i2c_delay();
    sda_high();
    soft_i2c_delay();
}

uint8_t soft_i2c_write_byte(uint8_t data)
{
    uint8_t bit;
    uint8_t ack;

    for (bit = 0U; bit < 8U; bit++)
    {
        if ((data & 0x80U) != 0U)
        {
            sda_high();
        }
        else
        {
            sda_low();
        }

        soft_i2c_delay();
        scl_high();
        soft_i2c_delay();
        scl_low();
        data <<= 1;
    }

    /* Nhả SDA để slave có thể kéo LOW gửi ACK. */
    sda_high();
    soft_i2c_delay();
    scl_high();
    soft_i2c_delay();
    ack = (sda_read() == 0U) ? 1U : 0U;
    scl_low();

    return ack;
}

uint8_t soft_i2c_read_byte(uint8_t send_ack)
{
    uint8_t bit;
    uint8_t data = 0U;

    /* Nhả SDA để slave điều khiển đường dữ liệu. */
    sda_high();

    for (bit = 0U; bit < 8U; bit++)
    {
        data <<= 1;
        scl_high();
        soft_i2c_delay();

        if (sda_read() != 0U)
        {
            data |= 0x01U;
        }

        scl_low();
        soft_i2c_delay();
    }

    if (send_ack != 0U)
    {
        sda_low();
    }
    else
    {
        sda_high();
    }

    soft_i2c_delay();
    scl_high();
    soft_i2c_delay();
    scl_low();
    sda_high();

    return data;
}
