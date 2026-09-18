/*
 * clock.c
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#include "clock.h"

/*==============================*/
/* Private Variable             */
/*==============================*/

static ClockTime_t current_time;

/*==============================*/
/* Private Function             */
/*==============================*/
void clock_set_time(const ClockTime_t *time){
	current_time = *time;
}

void clock_get_time(ClockTime_t *time){
	*time = current_time;
}

/*==============================*/
/* Public Function              */
/*==============================*/
void clock_update(){
	current_time.second++;
	if (current_time.second >= 60 )
	{current_time.minute++;current_time.second = 0;}
	if(current_time.minute >= 60 )
	{current_time.hour++;current_time.minute = 0;}
	if(current_time.hour >= 24)
	{
	    current_time.hour = 0;
	}
}

void clock_init(void)
{
    current_time.hour   = 0;
    current_time.minute = 0;
    current_time.second = 0;
}

// Hàm tăng giờ
void clock_hour_up(void)
{
    current_time.hour++;

    if(current_time.hour >= 24)
    {
        current_time.hour = 0;
    }
}

// Hàm giảm giờ
void clock_hour_down(void)
{
    if(current_time.hour == 0)
    {
        current_time.hour = 23;
    }
    else
    {
        current_time.hour--;
    }
}

// Hàm tăng phút
void clock_minute_up(void)
{
    current_time.minute++;

    if(current_time.minute >= 60)
    {
        current_time.minute = 0;
    }
}

// Hàm giảm phút
void clock_minute_down(void)
{
    if(current_time.minute == 0)
    {
        current_time.minute = 59;
    }
    else
    {
        current_time.minute--;
    }
}

// Hàm tăng giây
void clock_second_up(void)
{
    current_time.second++;

    if(current_time.second >= 60)
    {
        current_time.second = 0;
    }
}

// Hàm giảm giây
void clock_second_down(void)
{
    if(current_time.second == 0)
    {
        current_time.second = 59;
    }
    else
    {
        current_time.second--;
    }
}
