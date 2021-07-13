/*
 * sequences.c
 *
 *  Created on: Jul 13, 2021
 *      Author: ismaelminchala
 */
#include "sequences.h"

void positionRefresh( struct sequence_t *psequence );

int8_t nonBlockingDelay( uint32_t myDelay ){
	static uint32_t cont = 0;
	uint32_t nBase = myDelay / tBase;
	HAL_Delay(tBase);
	if ( cont > nBase * tBase ){
		cont = 0;
		return 1;
	} else{
		cont += tBase;
		return 0;
	}
}

void sequenceActivation( struct sequence_t *psequence, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[], uint32_t *seqTimes, uint8_t pos, uint8_t len ){
	psequence->ledPin = ledsPin;
	psequence->seqTimes = seqTimes;
	psequence->len = len;
	psequence->pos = pos;
	psequence->orientation = 0;
	//turnOffLEDs(ledsPin, ledsPort, psequence->len);
	turnOffLEDs();
	turnOnLED(psequence->ledPin, ledsPort, psequence->pos);
}

void sequenceActualization( struct sequence_t *psequence, uint16_t *ledsPin, GPIO_TypeDef *ledsPort[] ){
	if ( nonBlockingDelay(psequence->seqTimes[psequence->pos]) ){
		turnOffLEDs(ledsPin, ledsPort, psequence->len);
		positionRefresh(psequence);
		turnOnLED(psequence->ledPin, ledsPort, psequence->pos);
	}
}

void positionRefresh( struct sequence_t *psequence ){
	if ( psequence->orientation == 0) {
		if( psequence->pos < psequence->len - 1 ){
			++psequence->pos;
		} else{
			psequence->pos = 0;
		}
	} else{
		if( psequence->pos > 0 ){
					--psequence->pos;
				} else{
					psequence->pos = psequence->len - 1;
				}
	}
}
