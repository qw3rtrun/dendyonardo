/*
 * NESController.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: qw3rtrun
 */

#include "NESController.h"
#include "Arduino.h"

const int TICK = 2;
const int A = 0x80;
const int B = 0x40;
const int SELECT = 0x20;
const int START = 0x10;
const int UP = 0x04;
const int DOWN = 0x08;
const int LEFT = 0x02;
const int RIGHT = 0x01;

NESDriver::NESDriver(int latchPin, int clockPin) {
	_latchPin = latchPin;
	_clockPin = clockPin;
}

void NESDriver::begin() {
	pinMode(_latchPin, OUTPUT);
	digitalWrite(_latchPin, HIGH);
	pinMode(_clockPin, OUTPUT);
	digitalWrite(_clockPin, HIGH);
}

ControllerState NESDriver::read(int dataPin) {
	digitalWrite(_latchPin, LOW);
	delay(TICK);
	byte state = shiftIn(dataPin, _clockPin, MSBFIRST);
	digitalWrite(_latchPin, HIGH);
	struct ControllerState cs;
	return cs;
}
