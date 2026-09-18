/*
 * timer.h
 *
 *  Created on: Jul 7, 2026
 *      Author: nguye
 */

#ifndef TIMER_H
#define TIMER_H

#include "main.h"
#include "stdbool.h"


void timer_init(void);

uint32_t timer_get_tick(void);

bool timer_expired(uint32_t *previous_tick,
                      uint32_t interval);

#endif
