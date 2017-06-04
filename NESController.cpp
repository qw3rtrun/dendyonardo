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
	c1.begin(dataPin);
}

NESDriver::NESDriver(int latchPin, int clockPin, int dataPin1, int dataPin2) {
	_latchPin = latchPin;
	_clockPin = clockPin;
	_count = 2;
	c1.begin(dataPin1);
	c2.begin(dataPin2);
}

void NESDriver::begin() {
	pinMode(_latchPin, OUTPUT);
	digitalWrite(_latchPin, HIGH);
	pinMode(_clockPin, OUTPUT);
	digitalWrite(_clockPin, HIGH);
	readControllers();
}


String toStr(NESController c) {
  String r = "";
  r += (c.a() ? "A " : "a ");
  r += (c.b() ? "B " : "b ");
  r += (c.select() ? "SELECT " : "select ");
  r += (c.start() ? "START " : "start ");
  r += (c.up() ? "UP " : "");
  r += (c.down() ? "DOWN " : "");
  r += (c.left() ? "LEFT " : "");
  r += (c.right() ? "RIGHT " : "");
  return r;
}

void NESDriver::readControllers() {
	c1.checkChanges();
	digitalWrite(_latchPin, LOW);
  delayMicroseconds(6);
	for (int i = 0; i < 8; i++) {
		digitalWrite(_clockPin, LOW);
		delayMicroseconds(3);
		c1.read(i);
	//	c2.read(i);
	//	c3.read(i);
		//c4.read(i);
		digitalWrite(_clockPin, HIGH);
    delayMicroseconds(3);
	}
	digitalWrite(_latchPin, HIGH);
 Serial.print(c1.state() );
 Serial.print(" "+toStr(c1));
 Serial.println("");
}


NESController NESDriver::controller1() {
	return c1;
}

NESController NESDriver::controller2() {
	return c2;
}

NESController::NESController() {
	_dataPin = -1;
	_state = 0;
	_previousState = 0;
}

void NESController::begin(int dataPin) {
  pinMode(dataPin, INPUT);
	_dataPin = dataPin;
}

bool NESController::isConnected() {
	return _dataPin >= 0 &&_state != 0;
}

void NESController::read(int i) {
	if (_dataPin > 0) {
		int bit = digitalRead(_dataPin);
		_state = (_state << 1) | bit;
	}
}

bool NESController::checkChanges() {
	bool result = _state != _previousState;
	_previousState = _state;
	return result;
}

int NESController::state() {
	return _state;
}

bool NESController::button(int mask) {
	return isConnected() && !(_state & mask);
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





