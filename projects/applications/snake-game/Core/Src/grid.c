/*
 * grid.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */


#include "grid.h"

bool grid_is_valid(uint8_t x,
                   uint8_t y)
{
    return (x < GRID_WIDTH) &&
           (y < GRID_HEIGHT);
}
