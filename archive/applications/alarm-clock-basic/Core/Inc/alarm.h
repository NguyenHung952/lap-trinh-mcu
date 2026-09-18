/*
 * alarm.h
 *
 *  Created on: Jul 11, 2026
 *      Author: nguye
 */
#ifndef ALARM_H_
#define ALARM_H_
#define ALARM_ENABLE   1U
#define ALARM_DISABLE  0U
#include "main.h"
#include "clock.h"

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t enable;

} AlarmTime_t;

void alarm_init(void);
void alarm_update(void);

void alarm_set_time(uint8_t hour, uint8_t minute);
void alarm_get_time(AlarmTime_t *alarm);

void alarm_enable(void);
void alarm_disable(void);

void alarm_hour_up(void);
void alarm_hour_down(void);
void alarm_minute_up(void);
void alarm_minute_down(void);

uint8_t alarm_is_ringing(void);
void alarm_stop_ringing(void);

#endif
