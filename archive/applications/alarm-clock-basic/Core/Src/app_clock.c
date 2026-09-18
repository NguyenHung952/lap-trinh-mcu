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
/*==============================*/
/* Private Variable             */
/*==============================*/

static uint32_t last_tick;
static MenuEvent_t event;

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
    last_tick = timer_get_tick();
}

void app_clock_process(void)
{
	button_event_update();

	event = button_event_get();

	alarm_input_update(event);

	menu_process(event);

	switch(menu_get_state())
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
	}

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
    if(timer_expired(&last_tick,1000))//Chỉnh tốc độ chạy thời gian 1000msx4 =3600ms
    {
        clock_update();
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
    if (!alarm_is_ringing())
    {
        return;
    }

    if (event != MENU_EVENT_NONE)
    {
        alarm_stop_ringing();
    }
}
