/*
 * keyboard.h
 *
 *  Created on: Jul 12, 2021
 *      Author: ismaelminchala
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "stm32f4xx_hal.h"

int8_t readKey( GPIO_TypeDef *keyPort, uint16_t keyPin );

#endif /* INC_KEYBOARD_H_ */
