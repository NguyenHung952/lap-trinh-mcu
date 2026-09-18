/*
 * app_clock.c
 *
 *  Created on: Jul 9, 2026
 *      Author: nguye
 */

#include "app_clock.h"
#include "lcd.h"
#include "clock.h"
#include "menu.h"
#include "button_event.h"
#include "ui.h"
#include "timer.h"
#include "alarm.h"
#include "buzzer.h"
#include "led.h"
#include "ds3231.h"

/*==============================*/
/* Private Variable             */
/*==============================*/

/*
 * Các biến debug có thể theo dõi bằng Live Expressions.
 */
static uint8_t ds3231_connected;

static uint8_t rtc_time_valid;
static uint8_t rtc_write_ok;
static Ds3231Time_t rtc_time;

static uint8_t temperature_valid;
static int16_t temperature_quarter_c;

static uint8_t sda_idle;
static uint8_t scl_idle;

/*
 * TIM1 được dùng làm chu kỳ đọc RTC và làm nguồn thời gian dự phòng.
 */
static uint32_t last_clock_tick;
static uint32_t last_temperature_tick;

static MenuEvent_t event;
static MenuState_t previous_menu_state;
static MenuState_t current_menu_state;

/*==============================*/
/* Private Function             */
/*==============================*/

static void app_process_normal(void);

static void app_process_set_hour(MenuEvent_t event);

static void app_process_set_minute(MenuEvent_t event);

static void app_process_set_second(MenuEvent_t event);

static void app_process_set_alarm_hour(MenuEvent_t event);

static void app_process_set_alarm_minute(MenuEvent_t event);

static void app_process_set_alarm_enable(MenuEvent_t event);

static void alarm_input_update(MenuEvent_t event);

static void app_temperature_update(void);

static void app_rtc_read_and_update_clock(void);

static void app_rtc_save_after_time_setting(void);

/*==============================*/
/* Public Function              */
/*==============================*/

void app_clock_init(void)
{
    timer_init();

    clock_init();

    alarm_init();

    menu_init();

    button_event_init();

    ui_init();

    last_clock_tick = timer_get_tick();

    last_temperature_tick = timer_get_tick();

    ds3231_init();

    /*
     * Khi bus rảnh, SDA và SCL phải bằng 1.
     */
    sda_idle = HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);

    scl_idle = HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin);

    ds3231_connected = ds3231_is_connected();

    rtc_time_valid = 0U;
    rtc_write_ok = 0U;

    temperature_valid = 0U;
    temperature_quarter_c = 0;

    if(ds3231_connected != 0U)
    {
        /*
         * Đọc giờ thật ngay khi khởi động.
         */
        app_rtc_read_and_update_clock();

        temperature_valid =
            ds3231_read_temperature(&temperature_quarter_c);
    }

    ui_set_temperature(temperature_quarter_c,
                       temperature_valid);
}

void app_clock_process(void)
{
    button_event_update();

    event = button_event_get();

    /*
     * Lưu trạng thái trước khi menu xử lý sự kiện.
     * Việc này giúp phát hiện lúc vừa chỉnh xong giây.
     */
    previous_menu_state = menu_get_state();

    alarm_input_update(event);

    menu_process(event);

    current_menu_state = menu_get_state();

    /*
     * Khi bấm NEXT tại MENU_SET_SECOND, menu chuyển sang
     * MENU_SET_ALARM_HOUR. Lúc đó ghi thời gian vừa chỉnh
     * vào DS3231 đúng một lần.
     */
    if((previous_menu_state == MENU_SET_SECOND) &&
       (current_menu_state == MENU_SET_ALARM_HOUR) &&
       (event == MENU_EVENT_NEXT))
    {
        app_rtc_save_after_time_setting();
    }

    switch(current_menu_state)
    {
        case MENU_NORMAL:
            app_process_normal();
            break;

        case MENU_SET_HOUR:
            app_process_set_hour(event);
            break;

        case MENU_SET_MINUTE:
            app_process_set_minute(event);
            break;

        case MENU_SET_SECOND:
            app_process_set_second(event);
            break;

        case MENU_SET_ALARM_HOUR:
            app_process_set_alarm_hour(event);
            break;

        case MENU_SET_ALARM_MINUTE:
            app_process_set_alarm_minute(event);
            break;

        case MENU_SET_ALARM_ENABLE:
            app_process_set_alarm_enable(event);
            break;

        default:
            break;
    }

    app_temperature_update();

    alarm_update();

    if(alarm_is_ringing())
    {
        buzzer_on();
        led_on();
    }
    else
    {
        buzzer_off();
        led_off();
    }

    ui_update();
}

/*==============================*/
/* Private Function             */
/*==============================*/

static void app_process_normal(void)
{
    if(timer_expired(&last_clock_tick, 1000U))
    {
        ds3231_connected = ds3231_is_connected();

        if(ds3231_connected != 0U)
        {
            /*
             * DS3231 là nguồn thời gian chính.
             */
            app_rtc_read_and_update_clock();
        }
        else
        {
            rtc_time_valid = 0U;

            /*
             * Nếu mất kết nối RTC, đồng hồ vẫn chạy bằng TIM1.
             */
            clock_update();
        }
    }
}

static void app_rtc_read_and_update_clock(void)
{
    ClockTime_t clock_time;

    rtc_time_valid = ds3231_read_time(&rtc_time);

    if(rtc_time_valid == 0U)
    {
        return;
    }

    clock_time.hour = rtc_time.hour;
    clock_time.minute = rtc_time.minute;
    clock_time.second = rtc_time.second;

    clock_set_time(&clock_time);
}

static void app_rtc_save_after_time_setting(void)
{
    ClockTime_t clock_time;

    clock_get_time(&clock_time);

    rtc_time.hour = clock_time.hour;
    rtc_time.minute = clock_time.minute;
    rtc_time.second = clock_time.second;

    ds3231_connected = ds3231_is_connected();

    if(ds3231_connected != 0U)
    {
        rtc_write_ok = ds3231_write_time(&rtc_time);
    }
    else
    {
        rtc_write_ok = 0U;
    }

    /*
     * Bắt đầu chu kỳ đọc mới kể từ lúc vừa ghi giờ,
     * tránh đọc lại ngay trong cùng thời điểm.
     */
    last_clock_tick = timer_get_tick();
}

static void app_temperature_update(void)
{
    if(timer_expired(&last_temperature_tick, 1000U))
    {
        ds3231_connected = ds3231_is_connected();

        if(ds3231_connected != 0U)
        {
            temperature_valid =
                ds3231_read_temperature(&temperature_quarter_c);
        }
        else
        {
            temperature_valid = 0U;
        }

        ui_set_temperature(temperature_quarter_c,
                           temperature_valid);
    }
}

static void app_process_set_hour(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            clock_hour_up();
            break;

        case MENU_EVENT_DOWN:
            clock_hour_down();
            break;

        default:
            break;
    }
}

static void app_process_set_minute(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            clock_minute_up();
            break;

        case MENU_EVENT_DOWN:
            clock_minute_down();
            break;

        default:
            break;
    }
}

static void app_process_set_second(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            clock_second_up();
            break;

        case MENU_EVENT_DOWN:
            clock_second_down();
            break;

        default:
            break;
    }
}

static void app_process_set_alarm_hour(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            alarm_hour_up();
            break;

        case MENU_EVENT_DOWN:
            alarm_hour_down();
            break;

        default:
            break;
    }
}

static void app_process_set_alarm_minute(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            alarm_minute_up();
            break;

        case MENU_EVENT_DOWN:
            alarm_minute_down();
            break;

        default:
            break;
    }
}

static void app_process_set_alarm_enable(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_UP:
            alarm_enable();
            break;

        case MENU_EVENT_DOWN:
            alarm_disable();
            break;

        default:
            break;
    }
}

static void alarm_input_update(MenuEvent_t event)
{
    if(!alarm_is_ringing())
    {
        return;
    }

    if(event != MENU_EVENT_NONE)
    {
        alarm_stop_ringing();
    }
}
