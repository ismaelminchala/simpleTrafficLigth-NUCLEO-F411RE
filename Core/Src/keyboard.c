/*
 * keyboard.c
 *
 *  Created on: Jul 12, 2021
 *      Author: ismaelminchala
 */


#include "keyboard.h"

int8_t readKey( GPIO_TypeDef *keyPort, uint16_t keyPin )
{
	if ( !HAL_GPIO_ReadPin(keyPort, keyPin) ){
		HAL_Delay(100);
		return 1;
	} else
	{
		return 0;
	}
}
