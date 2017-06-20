#include "NESAdapter.h"

NESAdapter::NESAdapter(int joyId) {
	joy = Joystick_(joyId, JOYSTICK_TYPE_GAMEPAD, 6, 0, // Button Count, Hat Switch Count
			true, true, false,     // X and Y, but no Z Axis
			false, false, false,   // No Rx, Ry, or Rz
			false, false,          // No rudder or throttle
			false, false, false);
}

void NESAdapter::begin() {
	joy.begin(false);
	joy.setXAxisRange(-1, 1);
	joy.setYAxisRange(-1, 1);
}

void NESAdapter::reset() {
	setA(false);
	setB(false);
	setStart(false);
	setSelect(false);
	setX(0);
	setY(0);
	setL(false);
	setR(false);
}

void NESAdapter::setA(bool pushed) {
	changed = changed || pushed != a;
	a = pushed;
	joy.setButton(0, pushed);
}


void NESAdapter::setB(bool pushed) {
	changed = changed || pushed != b;
	b = pushed;
	joy.setButton(1, pushed);
}


void NESAdapter::setStart(bool pushed) {
	changed = changed || pushed != start;
	start = pushed;
	joy.setButton(2, pushed);
}

void NESAdapter::setSelect(bool pushed) {
	changed = changed || pushed != select;
	select = pushed;
	joy.setButton(3, pushed);
}


void NESAdapter::setY(int _y) {
	changed = changed || _y != y;
	y = _y;
	joy.setYAxis(_y);
}

void NESAdapter::setX(int _x) {
	changed = changed || _x != x;
	x = _x;
	joy.setXAxis(_x);
}


void NESAdapter::setL(bool pushed) {
	changed = changed || pushed != l;
	l = pushed;
	joy.setButton(4, pushed);
}

void NESAdapter::setR(bool pushed) {
	changed = changed || pushed != r;
	r = pushed;
	joy.setButton(5, pushed);

}

void NESAdapter::sendState() {
	if (changed) {
		joy.sendState();
	}
	changed = false;
}
