/*
 * ui.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */


#include "ui.h"
#include <stdio.h>
#include "lcd.h"

#define CURSOR_HOUR_COL      0
#define CURSOR_MINUTE_COL    3
#define CURSOR_SECOND_COL    6
/*==============================*/
/* Private Variable             */
/*==============================*/

static ClockTime_t current_time;

static MenuState_t current_state;

/*==============================*/
/* Private Function             */
/*==============================*/

static void ui_show_normal(void);

static void ui_show_set_hour(void);

static void ui_show_set_minute(void);

static void ui_show_set_second(void);

static void ui_show_time(void);

static void ui_show_status(const char *text);
/*==============================*/
/* Public Function              */
/*==============================*/

void ui_init(void)
{

}

void ui_update(void)
{
    clock_get_time(&current_time);

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

        default:
            break;
    }
}

/*==============================*/
/* Private Function             */
/*==============================*/
static void ui_show_time(void)
{
    char str[16];

    sprintf(str, "%02d:%02d:%02d",
            current_time.hour,
            current_time.minute,
            current_time.second);

    lcd_set_cursor(0,0);
    lcd_print(str);
}

static void ui_show_normal(void)
{
    ui_show_time();

    lcd_cursor_off();
    lcd_blink_off();

    lcd_set_cursor(1,0);
    lcd_print("DIGITAL CLOCK ");
}

static void ui_show_set_hour(void)
{
    ui_show_time();

    lcd_set_cursor(0,0);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET HOUR");
}

static void ui_show_set_minute(void)
{
    ui_show_time();

    lcd_set_cursor(0,3);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET MIN");
}

static void ui_show_set_second(void)
{
    ui_show_time();

    lcd_set_cursor(0,6);

    lcd_cursor_on();
    lcd_blink_on();

    ui_show_status("SET SEC");
}

static void ui_show_status(const char *text)
{
    lcd_set_cursor(1,0);

    lcd_print("                ");

    lcd_set_cursor(1,0);

    lcd_print(text);
}

