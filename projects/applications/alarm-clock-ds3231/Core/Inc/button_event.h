/*
 * button_event.h
 *
 *  Created on: Jul 8, 2026
 *      Author: nguye
 */

#ifndef BUTTON_EVENT_H_
#define BUTTON_EVENT_H_

#include "menu.h"

/*==============================*/
/* Public API                   */
/*==============================*/

void button_event_init(void);

void button_event_update(void);

MenuEvent_t button_event_get(void);

#endif /* BUTTON_EVENT_H_ */
