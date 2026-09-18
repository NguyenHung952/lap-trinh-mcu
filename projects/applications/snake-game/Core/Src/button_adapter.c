/*
 * button_adapter.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "button_adapter.h"

#include "button.h"

bool button_adapter_get_direction(SnakeDirection_t *direction)
{
    if (direction == NULL)
    {
        return false;
    }

    uint8_t button_data = Read74HC165();

    if (ButtonPressed(button_data, BUTTON_UP))
    {
        *direction = DIR_UP;
        return true;
    }

    if (ButtonPressed(button_data, BUTTON_DOWN))
    {
        *direction = DIR_DOWN;
        return true;
    }

    if (ButtonPressed(button_data, BUTTON_LEFT))
    {
        *direction = DIR_LEFT;
        return true;
    }

    if (ButtonPressed(button_data, BUTTON_RIGHT))
    {
        *direction = DIR_RIGHT;
        return true;
    }

    return false;
}
