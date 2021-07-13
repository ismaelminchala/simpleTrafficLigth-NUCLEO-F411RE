/**
  ******************************************************************************
  * @file           : leds.h
  * @brief          : Module related to the LEDS control on the NUCLEO-F411RE
  *                   board.
  ******************************************************************************
  */


#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include "stm32f4xx_hal.h"
#define BLACKOUT 0


void turnOnLED(uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint8_t pos);

//void turnOffLEDs(uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint8_t len);
void turnOffLEDs();


#endif /* INC_LEDS_H_ */
