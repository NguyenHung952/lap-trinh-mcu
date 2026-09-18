/*
 * renderer_utils.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include <stdint.h>

#define RENDER_CELL_SIZE 4

void renderer_draw_cell(uint8_t cell_x,
                        uint8_t cell_y,
                        uint8_t color);

#endif
