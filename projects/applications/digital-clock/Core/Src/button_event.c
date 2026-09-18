/*
 * button_event.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#include "button_event.h"
#include "button.h"

/*==============================*/
/* Private Variable             */
/*==============================*/

static MenuEvent_t current_event;

/*==============================*/
/* Private Function             */
/*==============================*/

static void button_event_decode(uint8_t data);

/*==============================*/
/* Public Function              */
/*==============================*/

void button_event_init(void)
{
    current_event = MENU_EVENT_NONE;
}

void button_event_update(void)
{
    uint8_t data = Read74HC165();

    button_event_decode(data);
}

MenuEvent_t button_event_get(void)
{
    MenuEvent_t event = current_event;

    current_event = MENU_EVENT_NONE;

    return event;
}

/*==============================*/
/* Private Function             */
/*==============================*/

static void button_event_decode(uint8_t data)
{
    current_event = MENU_EVENT_NONE;

    if(ButtonPressed(data,0))
    {
        current_event = MENU_EVENT_SET;
    }
    else if(ButtonPressed(data,1))
    {
        current_event = MENU_EVENT_NEXT;
    }
    else if(ButtonPressed(data,2))
    {
        current_event = MENU_EVENT_UP;
    }
    else if(ButtonPressed(data,3))
    {
        current_event = MENU_EVENT_DOWN;
    }
}
