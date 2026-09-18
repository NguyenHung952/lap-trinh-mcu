/*
 * random.c
 *
 *  Created on: Jul 17, 2026
 *      Author: nguye
 */

#include "random.h"

#define RANDOM_DEFAULT_SEED    0xACE1

static uint16_t random_state = RANDOM_DEFAULT_SEED;

void random_init(uint32_t seed)
{
    if (seed != 0)
    {
        random_state = (uint16_t)seed;
    }
    else
    {
        random_state = RANDOM_DEFAULT_SEED;
    }
}

uint16_t random_get(void)
{
    uint16_t bit;

    bit = ((random_state >> 0)
        ^  (random_state >> 2)
        ^  (random_state >> 3)
        ^  (random_state >> 5)) & 1;

    random_state = (random_state >> 1)
                 | (bit << 15);

    return random_state;
}

uint16_t random_range(uint16_t min,
                      uint16_t max)
{
    if (max <= min)
    {
        return min;
    }

    uint32_t range = (uint32_t)max - min + 1U;

    return min + (random_get() % range);
}
