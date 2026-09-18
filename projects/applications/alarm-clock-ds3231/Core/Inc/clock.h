/*
 * clock.h
 *
 *  Created on: Jul 9, 2026
 *      Author: nguye
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

/*==============================*/
/* Data Type                    */
/*==============================*/

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

} ClockTime_t;

/*==============================*/
/* Public API                   */
/*==============================*/

void clock_init(void);
void clock_hour_up(void);
void clock_hour_down(void);

void clock_minute_up(void);
void clock_minute_down(void);

void clock_second_up(void);
void clock_second_down(void);
void clock_update(void);

void clock_set_time(const ClockTime_t *time);

void clock_get_time(ClockTime_t *time);

#endif /* CLOCK_H_ */
