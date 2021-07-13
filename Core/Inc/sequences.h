/*
 * sequences.h
 *
 *  Created on: Jul 13, 2021
 *      Author: ismaelminchala
 */

#ifndef INC_SEQUENCES_H_
#define INC_SEQUENCES_H_


#define tBase 10
#include "stm32f4xx_hal.h"

struct sequence_t {
	uint16_t	*ledPin;
	uint8_t 	len;
	uint32_t 	*seqTimes;
	uint8_t 	orientation;
	uint8_t		pos;
};


int8_t nonBlockingDelay( uint32_t myDelay );

void sequenceActivation( struct sequence_t *psequence, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint32_t *seqTimes, uint8_t pos, uint8_t len );

void sequenceActualization( struct sequence_t *psequence, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] );

#endif /* INC_SEQUENCES_H_ */
