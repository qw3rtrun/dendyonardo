/*
 * NESController.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: qw3rtrun
 */

#include "NESController.h"
#include "Arduino.h"

NESDriver::NESDriver(int latchPin, int clockPin, int dataPin) {
	_latchPin = latchPin;
	_clockPin = clockPin;
	_count = 1;
	_cs = {new NESController(dataPin)};
}

NESDriver::NESDriver(int latchPin, int clockPin, int dataPin1, int dataPin2) {
	_latchPin = latchPin;
	_clockPin = clockPin;
	_count = 2;
	_cs = {new NESController(dataPin1), new NESController(dataPin2)};
}

void NESDriver::begin() {
	pinMode(_latchPin, OUTPUT);
	digitalWrite(_latchPin, LOW);
	pinMode(_clockPin, OUTPUT);
	digitalWrite(_clockPin, LOW);
	readControllers();
}

void NESDriver::readControllers() {
	digitalWrite(_latchPin, HIGH);
	delayMicroseconds(6);
	digitalWrite(_latchPin, LOW);
	for (int i = 0; i < 8; i++) {
		for (int c = 0; c <= _count; c++) {
			_cs[c].read(i);
		}
		digitalWrite(_clockPin, HIGH);
		digitalWrite(_clockPin, LOW);
	}
}

NESController NESDriver::controller1() {
	return _cs[0];
}

NESController NESDriver::controller2() {
	return _cs[_count > 1 ? 1 : 0];
}

NESController::NESController(int dataPin) {
	_dataPin = dataPin;
	_state = 0;
	_previousState = 0;
}

bool NESController::isConnected() {
	return _state != 0;
}

void NESController::read(int i) {
	int bit = digitalRead(_dataPin);
	_state = (_state << (7-i)) | bit;
}

bool NESController::checkChanges() {
	bool result = _state != _previousState;
	_previousState = _state;
	return result;
}

bool NESController::button(int mask) {
	return isConnected && (_state & mask);
}

bool NESController::a() {
	return button(A);
}

bool NESController::b() {
	return button(B);
}

bool NESController::select() {
	return button(SELECT);
}

bool NESController::start() {
	return button(START);
}

bool NESController::up() {
	return button(UP);
}

bool NESController::down() {
	return button(DOWN);
}

int NESController::xAxis() {
	return button(UP) - button(DOWN);
}

bool NESController::right() {
	return button(RIGHT);
}

bool NESController::left() {
	return button(LEFT);
}

int NESController::yAxis() {
	return button(RIGHT) - button(LEFT);
}





