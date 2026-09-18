/*
 * led.c
 *
 *  Created on: Jul 7, 2026
 *      Author: nguye
 */
#include "main.h"

void led_off(void){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1);
	  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1);
	  HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 1);
	  HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, 1);
	  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, 1);
}

void led_on(void){
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);
	  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0);
	  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0);
	  HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
	  HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, 0);
	  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, 0);
}

void led_loading(void){
			HAL_GPIO_WritePin(COI_GPIO_Port, COI_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COI_GPIO_Port, COI_Pin, GPIO_PIN_SET);
			led_off();
			HAL_Delay(100);
			led_on();
			HAL_Delay(100);
			led_off();
			HAL_GPIO_WritePin(COI_GPIO_Port, COI_Pin, GPIO_PIN_RESET);

}
