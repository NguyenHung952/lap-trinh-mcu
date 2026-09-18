/*
 * render.h
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <stdbool.h>

#include "framebuffer.h"

#define RENDER_BLOCK_ROWS FB_BLOCK_ROWS
#define RENDER_BLOCK_COLS FB_BLOCK_COLS

typedef struct
{
    uint8_t pattern[FB_BLOCK_H];
    bool dirty;

} RenderBlock_t;

extern RenderBlock_t render_buffer[RENDER_BLOCK_ROWS][RENDER_BLOCK_COLS];

void render_init(void);

void render_update(void);

#endif
