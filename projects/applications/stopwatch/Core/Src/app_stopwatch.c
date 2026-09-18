/*
 * app_stopwatch.c
 */

#include "main.h"
#include "lcd.h"
#include "led.h"
#include "button.h"
#include "timer.h"
#include <stdbool.h>

/*==========================
 * State Machine
 *==========================*/
typedef enum
{
    STOPWATCH_STOP = 0,
    STOPWATCH_RUN,
    STOPWATCH_PAUSE

} StopwatchState;

/*==========================
 * Static Variables
 *==========================*/

static StopwatchState state;

static uint32_t elapsed_ms;
static uint32_t last_tick;

static uint8_t button_data;

static uint32_t display_time = 0xFFFFFFFF;
static StopwatchState display_state;

/*==========================
 * Private Function Prototype
 *==========================*/

static void stopwatch_reset(void);
static void stopwatch_read_button(void);
static void stopwatch_update_state(void);
static void stopwatch_update_time(void);
static void stopwatch_update_display(void);
static void stopwatch_update_led(void);

/*==========================
 * Public API
 *==========================*/

void app_stopwatch_init(void)
{
    state = STOPWATCH_STOP;

    elapsed_ms = 0;

    last_tick = timer_get_tick();

    button_data = 0;

    stopwatch_update_display();
    stopwatch_update_led();
}

void app_stopwatch_process(void)
{
    stopwatch_read_button();

    stopwatch_update_state();

    stopwatch_update_time();

    stopwatch_update_display();

    stopwatch_update_led();
}

/*==========================
 * Private Functions
 *==========================*/

static void stopwatch_reset(void)
{
    elapsed_ms = 0;
    last_tick = timer_get_tick();
}

static void stopwatch_read_button(void)
{
    button_data = Read74HC165();
    if(button_data == 0x00)
    {
        lcd_set_cursor(1,10);
        lcd_print("00");
    }
    else if(button_data == 0xFF)
    {
        lcd_set_cursor(1,10);
        lcd_print("FF");
    }
}

static void stopwatch_update_state(void)
{
    bool start  = ButtonPressed(button_data, BUTTON_START);
    bool pause  = ButtonPressed(button_data, BUTTON_PAUSE);
    bool stop   = ButtonPressed(button_data, BUTTON_STOP);
    bool resume = ButtonPressed(button_data, BUTTON_RESUME);

    switch(state)
    {
        case STOPWATCH_STOP:

            if(start)
            {
                state = STOPWATCH_RUN;
            }

            break;

        case STOPWATCH_RUN:

            if(pause)
            {
                state = STOPWATCH_PAUSE;
            }
            else if(stop)
            {
                state = STOPWATCH_STOP;
                stopwatch_reset();
            }

            break;

        case STOPWATCH_PAUSE:

            if(resume)
            {
                state = STOPWATCH_RUN;
            }
            else if(stop)
            {
                state = STOPWATCH_STOP;
                stopwatch_reset();
            }

            break;
    }
}

static void stopwatch_update_time(void)
{
    if(state != STOPWATCH_RUN)
    {
        return;
    }

    if(timer_expired(&last_tick,100))
    {
        elapsed_ms += 100;
    }
}

static void stopwatch_update_display(void)
{
    uint32_t hours;
    uint32_t seconds_total;
    uint32_t minutes;
    uint32_t seconds;

    char buffer[9];

    seconds_total = elapsed_ms / 1000;

    hours = seconds_total / 3600;

    minutes = (seconds_total % 3600) / 60;

    seconds = seconds_total % 60;

    if ((display_time == elapsed_ms) &&
        (display_state == state))
    {
        return;
    }

    display_time = elapsed_ms;
    display_state = state;

    /* TODO:
       Chuyển minutes/seconds/milliseconds
       thành chuỗi trong buffer */

    buffer[0] = (hours / 10) + '0';
    buffer[1] = (hours % 10) + '0';

    buffer[2] = ':';

    buffer[3] = (minutes / 10) + '0';
    buffer[4] = (minutes % 10) + '0';

    buffer[5] = ':';

    buffer[6] = (seconds / 10) + '0';
    buffer[7] = (seconds % 10) + '0';

    buffer[8] = '\0';

    lcd_set_cursor(0,0);
    lcd_print(buffer);

    lcd_set_cursor(1,0);

    switch(state)
    {
        case STOPWATCH_STOP:

            lcd_print("STOP ");

            break;

        case STOPWATCH_RUN:

            lcd_print("RUN  ");

            break;

        case STOPWATCH_PAUSE:

            lcd_print("PAUSE");

            break;
    }
}

static void stopwatch_update_led(void)
{
    switch(state)
    {
        case STOPWATCH_STOP:

            led_off();

            break;

        case STOPWATCH_RUN:

            led_on();

            break;

        case STOPWATCH_PAUSE:

            led_loading();

            break;
    }
}
