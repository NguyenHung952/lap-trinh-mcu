/*
 * menu.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */


#include "menu.h"

/*==============================*/
/* Private Variable             */
/*==============================*/

static MenuState_t current_state;

/*==============================*/
/* Private Function             */
/*==============================*/

static void menu_normal(MenuEvent_t event);

static void menu_set_hour(MenuEvent_t event);

static void menu_set_minute(MenuEvent_t event);

static void menu_set_second(MenuEvent_t event);

static void menu_set_alarm_hour(MenuEvent_t event);

static void menu_set_alarm_minute(MenuEvent_t event);

static void menu_set_alarm_enable(MenuEvent_t event);
/*==============================*/
/* Public Function              */
/*==============================*/

void menu_init(void)
{
    current_state = MENU_NORMAL;
}

MenuState_t menu_get_state(void)
{
    return current_state;
}

void menu_process(MenuEvent_t event)
{
    switch(current_state)
    {
        case MENU_NORMAL:
            menu_normal(event);
            break;

        case MENU_SET_HOUR:
            menu_set_hour(event);
            break;

        case MENU_SET_MINUTE:
            menu_set_minute(event);
            break;

        case MENU_SET_SECOND:
            menu_set_second(event);
            break;

        case MENU_SET_ALARM_HOUR:
            menu_set_alarm_hour(event);
            break;

        case MENU_SET_ALARM_MINUTE:
            menu_set_alarm_minute(event);
            break;

        case MENU_SET_ALARM_ENABLE:
            menu_set_alarm_enable(event);
            break;

        default:
            current_state = MENU_NORMAL;
            break;
    }
}

/*==============================*/
/* Private Function             */
/*==============================*/

static void menu_normal(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_SET:
            current_state = MENU_SET_HOUR;
            break;

        default:
            break;
    }
}

static void menu_set_hour(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_NEXT:
            current_state = MENU_SET_MINUTE;
            break;

        default:
            break;
    }
}

static void menu_set_minute(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_NEXT:
            current_state = MENU_SET_SECOND;
            break;

        default:
            break;
    }
}

static void menu_set_second(MenuEvent_t event)
{
    switch(event)
    {
    	case MENU_EVENT_NEXT:
    		current_state = MENU_SET_ALARM_HOUR;
    		break;

        default:
            break;
    }
}

static void menu_set_alarm_hour(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_NEXT:
            current_state = MENU_SET_ALARM_MINUTE;
            break;

        default:
            break;
    }
}

static void menu_set_alarm_minute(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_NEXT:
            current_state = MENU_SET_ALARM_ENABLE;
            break;

        default:
            break;
    }
}

static void menu_set_alarm_enable(MenuEvent_t event)
{
    switch(event)
    {
        case MENU_EVENT_NEXT:
            current_state = MENU_NORMAL;
            break;

        default:
            break;
    }
}
