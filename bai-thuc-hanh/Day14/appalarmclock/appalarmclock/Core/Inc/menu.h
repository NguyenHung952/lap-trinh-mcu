/*
 * menu.h
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>

/*==============================*/
/* Menu State                   */
/*==============================*/
typedef enum
{
    MENU_NORMAL = 0,

    MENU_SET_HOUR,
    MENU_SET_MINUTE,
    MENU_SET_SECOND,

    MENU_SET_ALARM_HOUR,
    MENU_SET_ALARM_MINUTE,
    MENU_SET_ALARM_ENABLE

} MenuState_t;
/*==============================*/
/* Menu Event                   */
/*==============================*/
typedef enum
{
    MENU_EVENT_NONE = 0,

    MENU_EVENT_SET,

    MENU_EVENT_NEXT,

    MENU_EVENT_UP,

    MENU_EVENT_DOWN,

    MENU_EVENT_CONFIRM,

    MENU_EVENT_CANCEL,

} MenuEvent_t;

/*==============================*/
/* Public API                   */
/*==============================*/

void menu_init(void);

void menu_process(MenuEvent_t event);

MenuState_t menu_get_state(void);

#endif
