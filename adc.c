/*
 * ADC.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Ahmed Hassan
 */
#include <avr/io.h>
#include "types.h"
#include "macros.h"
#include "dio.h"

void adc_start(void) {
	setBit(ADCSRA,6);
}

void adc_vid_init (u8 pin) {
	//V_REF = 5V
	clrBit(ADMUX,6);
	clrBit(ADMUX,7);
	//NO LEFT ADJ
	clrBit(ADMUX,5);
	//CHANNEL 0 SINGLE
	clrBit(ADMUX,4);
	clrBit(ADMUX,3);
	clrBit(ADMUX,2);
	clrBit(ADMUX,1);
	clrBit(ADMUX,0);
	ADMUX = ADMUX | pin;
	//PRESCALAR 128
	setBit(ADCSRA,0);
	setBit(ADCSRA,1);
	setBit(ADCSRA,2);
	//DISABLE INTERUPT
	clrBit(ADCSRA,3);
	//ENABLE ADC
	setBit(ADCSRA,7);
	//ADC START CONVERSION
	adc_start();
}

u8 adc_u8_get_result(u16* result) {
	if (getBit(ADCSRA,4)) {
		ADCW&=(0b0000001111111111);
		*result = ADCW;
		setBit(ADCSRA,4);
		adc_start();
		return 1;
	}
	return 0;
}

