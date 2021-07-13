/*
 * leds.c
 *
 *  Created on: Jul 12, 2021
 *      Author: ismaelminchala
 */

#include "leds.h"

const uint16_t pins[] = {GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9};
const GPIO_TypeDef *ports[] = {GPIOA, GPIOA, GPIOA, GPIOA, BLACKOUT};
const uint8_t numLEDS = sizeof(pins)/sizeof(*pins);

void turnOnLED(uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint8_t pos)
{
	HAL_GPIO_WritePin(ledsPort[pos], ledsPin[pos], GPIO_PIN_SET);
}

//void turnOffLEDs(uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint8_t len){
void turnOffLEDs(){
	/*for (int8_t i = 0; i < len; ++i){
		HAL_GPIO_WritePin(ledsPort[i], ledsPin[i], GPIO_PIN_RESET);
	}*/

	for (int8_t i = 0; i < numLEDS; ++i){
		HAL_GPIO_WritePin(ports[i], pins[i], GPIO_PIN_RESET);
	}
}

