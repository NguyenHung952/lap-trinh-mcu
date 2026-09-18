/*
 * alarm.c
 *
 *  Created on: Jul 11, 2026
 *      Author: nguye
 */
#include "alarm.h"
#include "clock.h"
#include "led.h"
/* Private Variables */

static AlarmTime_t current_alarm;

static uint8_t ringing;

/* Private Functions */


uint8_t alarm_is_ringing(void)
{
    return ringing;
}

void alarm_stop_ringing(void)
{
	ringing = 0;
}


/* Public Functions */
void alarm_init(void)
{
	current_alarm.hour = 0;
	current_alarm.minute = 0;
	current_alarm.enable = ALARM_DISABLE;

	ringing = 0;
}

void alarm_set_time(uint8_t hour,
                    uint8_t minute)
{
    current_alarm.hour = hour;
    current_alarm.minute = minute;
}

void alarm_get_time(AlarmTime_t *alarm){
    *alarm = current_alarm;

}

void alarm_enable(void)
{
	current_alarm.enable = ALARM_ENABLE;
}

void alarm_disable(void)
{
	current_alarm.enable = ALARM_DISABLE;

}

void alarm_hour_up(void)
{
	current_alarm.hour++;
	    if(current_alarm.hour >= 24)
	    {
	    	current_alarm.hour = 0;
	    }
}

void alarm_hour_down(void)
{
	if(current_alarm.hour == 0)
	    {
	        current_alarm.hour = 23;
	    }
	    else
	    {
	        current_alarm.hour--;
	    }
}

void alarm_minute_up(void)
{
	 current_alarm.minute++;

	    if(current_alarm.minute >= 60)
	    {
	        current_alarm.minute = 0;
	    }
}

void alarm_minute_down(void)
{
    if(current_alarm.minute == 0)
    {
        current_alarm.minute = 59;
    }
    else
    {
        current_alarm.minute--;
    }
}

void alarm_update(void)
{
    ClockTime_t time;

    /* Đọc thời gian hiện tại */
    clock_get_time(&time);

    /* Alarm có Enable không? */
    if (current_alarm.enable == ALARM_DISABLE)
    {
        return;
    }

    /* So sánh Hour */
    if (current_alarm.hour != time.hour)
    {
        return;
    }

    /* So sánh Minute */
    if (current_alarm.minute != time.minute)
    {
        return;
    }

    /* Chỉ báo thức khi giây = 0 */
    if (time.second != 0)
    {
        return;
    }

    /* Nếu đang ringing rồi thì thôi */
    if(ringing)
        return;

    /* Bật trạng thái báo thức */
    ringing = 1;
    led_on();        // hoặc buzzer_on()
}

