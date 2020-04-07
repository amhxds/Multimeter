/*
 * DIO.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Ahmed Hassan
 */

#include <avr/io.h>
#include "types.h"
#include "macros.h"

void dio_vid_set_port_direction (u8 portNumber, u8 direction) {
	switch (portNumber) {
	case 0:
		DDRA = direction;
		break;
	case 1:
		DDRB = direction;
		break;
	case 2:
		DDRC = direction;
		break;
	case 3:
		DDRD = direction;
		break;
	}
}


void dio_vid_set_port_value (u8 portNumber, u8 value) {
	switch (portNumber) {
	case 0:
		PORTA = value;
		break;
	case 1:
		PORTB = value;
		break;
	case 2:
		PORTC = value;
		break;
	case 3:
		PORTD = value;
		break;
	}
}

u8 dio_u8_read_port_value (u8 portNumber) {
	switch (portNumber) {
	case 0:
		return PINA;
		break;
	case 1:
		return PINB;
		break;
	case 2:
		return PINC;
		break;
	case 3:
		return PIND;
		break;
	}
	return 0;
}


u8 dio_u8_read_pin_value (u8 portNumber, u8 index) {
	u8 port = dio_u8_read_port_value(portNumber);
	return getBit(port, index);
}

void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value) {
	switch (portNumber) {
	case 0:
		if (value == 1)
			setBit(PORTA, index);
		else if (value == 0)
			clrBit(PORTA, index);
		break;
	case 1:
		if (value == 1)
			setBit(PORTB, index);
		else if (value == 0)
			clrBit(PORTB, index);
		break;
	case 2:
		if (value == 1)
			setBit(PORTC, index);
		else if (value == 0)
			clrBit(PORTC, index);
		break;
	case 3:
		if (value == 1)
			setBit(PORTD, index);
		else if (value == 0)
			clrBit(PORTD, index);
		break;
	}
}


void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction) {
	switch (portNumber) {
	case 0:
		if (direction == 1)
			setBit(DDRA, index);
		else if (direction == 0)
			clrBit(DDRA, index);
		break;
	case 1:
		if (direction == 1)
			setBit(DDRB, index);
		else if (direction == 0)
			clrBit(DDRB, index);
		break;
	case 2:
		if (direction == 1)
			setBit(DDRC, index);
		else if (direction == 0)
			clrBit(DDRC, index);
		break;
	case 3:
		if (direction == 1)
			setBit(DDRD, index);
		else if (direction == 0)
			clrBit(DDRD, index);
		break;
	}
}
