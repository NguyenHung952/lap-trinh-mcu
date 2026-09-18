/*
 * ui.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#include "ui.h"
#include <stdio.h>
#include "lcd.h"
#include "alarm.h"

#define CURSOR_HOUR_COL      0
#define CURSOR_MINUTE_COL    3
#define CURSOR_SECOND_COL    6

/*==============================*/
/* Private Variable             */
/*==============================*/

static ClockTime_t current_time;
static AlarmTime_t current_alarm;
static MenuState_t current_state;

static int16_t current_temperature_quarter_c;
static uint8_t current_temperature_valid;

/*==============================*/
/* Private Function             */
/*==============================*/

static void ui_show_normal(void);

static void ui_show_set_hour(void);

static void ui_show_set_minute(void);

static void ui_show_set_second(void);

static void ui_show_time(void);

static void ui_show_status(const char *text);

static void ui_show_alarm(void);

static void ui_show_set_alarm_hour(void);

static void ui_show_set_alarm_minute(void);

static void ui_show_set_alarm_enable(void);

/*==============================*/
/* Public Function              */
/*==============================*/

void ui_init(void)
{
    current_temperature_quarter_c = 0;
    current_temperature_valid = 0U;
}

void ui_set_temperature(int16_t temperature_quarter_c,
                        uint8_t temperature_valid)
{
    current_temperature_quarter_c = temperature_quarter_c;
    current_temperature_valid = temperature_valid;
}

void ui_update(void)
{
    clock_get_time(&current_time);

    alarm_get_time(&current_alarm);

    current_state = menu_get_state();

    switch(current_state)
    {
        case MENU_NORMAL:
            ui_show_normal();
            break;

        case MENU_SET_HOUR:
            ui_show_set_hour();
            break;

        case MENU_SET_MINUTE:
            ui_show_set_minute();
            break;

        case MENU_SET_SECOND:
            ui_show_set_second();
            break;

        case MENU_SET_ALARM_HOUR:
            ui_show_set_alarm_hour();
            break;

        case MENU_SET_ALARM_MINUTE:
            ui_show_set_alarm_minute();
            break;

        case MENU_SET_ALARM_ENABLE:
            ui_show_set_alarm_enable();
            break;

        default:
            break;
    }
}

/*==============================*/
/* Private Function             */
/*==============================*/

static void ui_show_time(void)
{
    char str[17];

    sprintf(str,
            "%02d:%02d:%02d",
            current_time.hour,
            current_time.minute,
            current_time.second);

    lcd_set_cursor(0, 0);
    lcd_print("                ");

    lcd_set_cursor(0, 0);
    lcd_print(str);
}

static void ui_show_normal(void)
{
    char str[17];
    int16_t absolute_quarters;
    int16_t whole_part;
    uint8_t fraction_part;
    char sign;

    /* Dòng 1: hiển thị thời gian */
    ui_show_time();

    lcd_cursor_off();
    lcd_blink_off();

    /* Xóa dòng 2 */
    lcd_set_cursor(1, 0);
    lcd_print("                ");

    if(current_temperature_valid == 0U)
    {
        lcd_set_cursor(1, 0);
        lcd_print("TEMP:SENSOR ERR");
        return;
    }

    absolute_quarters = current_temperature_quarter_c;

    if(absolute_quarters < 0)
    {
        absolute_quarters = -absolute_quarters;
        sign = '-';
    }
    else
    {
        sign = '+';
    }

    /*
     * DS3231 trả nhiệt độ theo đơn vị 0.25 độ C.
     *
     * Ví dụ:
     *   136 / 4 = 34 độ C
     *   136 % 4 = 0  -> .00
     *
     *   137 / 4 = 34 độ C
     *   137 % 4 = 1  -> .25
     */
    whole_part = absolute_quarters / 4;

    fraction_part =
        (uint8_t)((absolute_quarters % 4) * 25);

    /*
     * Không sử dụng %f để tránh phải bật printf float.
     *
     * Kết quả ví dụ:
     *   TEMP:+34.00 C
     */
    sprintf(str,
            "TEMP:%c%02d.%02d C",
            sign,
            whole_part,
            fraction_part);

    lcd_set_cursor(1, 0);
    lcd_print(str);
}

static void ui_show_set_hour(void)
{
    ui_show_time();

    lcd_set_cursor(0, CURSOR_HOUR_COL);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET HOUR");
}

static void ui_show_set_minute(void)
{
    ui_show_time();

    lcd_set_cursor(0, CURSOR_MINUTE_COL);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET MIN");
}

static void ui_show_set_second(void)
{
    ui_show_time();

    lcd_set_cursor(0, CURSOR_SECOND_COL);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET SEC");
}

static void ui_show_status(const char *text)
{
    lcd_set_cursor(1, 0);

    lcd_print("                ");

    lcd_set_cursor(1, 0);

    lcd_print(text);
}

static void ui_show_alarm(void)
{
    char str[17];

    sprintf(str,
            "%02d:%02d %-3s",
            current_alarm.hour,
            current_alarm.minute,
            current_alarm.enable ? "ON" : "OFF");

    lcd_set_cursor(0, 0);
    lcd_print("                ");

    lcd_set_cursor(0, 0);
    lcd_print(str);
}

static void ui_show_set_alarm_hour(void)
{
    ui_show_alarm();

    lcd_set_cursor(0, CURSOR_HOUR_COL);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET AL HOUR");
}

static void ui_show_set_alarm_minute(void)
{
    ui_show_alarm();

    lcd_set_cursor(0, CURSOR_MINUTE_COL);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET AL MIN");
}

static void ui_show_set_alarm_enable(void)
{
    ui_show_alarm();

    lcd_cursor_off();
    lcd_blink_off();

    ui_show_status("SET ALARM");
}
