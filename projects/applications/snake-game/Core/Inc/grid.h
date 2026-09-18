/*
 * grid.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stdint.h>

#define GRID_WIDTH      20
#define GRID_HEIGHT      4

bool grid_is_valid(uint8_t x,
                   uint8_t y);

#endif
