/*
 * Author Trunov S.
 * 
 * Connecting Dendy's (NES-clone) 15-pin Gamepad 
 * to PC via Arduino Leonardo (or Micro) as USB-HID
 * using Joystick library
 * https://github.com/MHeironimus/ArduinoJoystickLibrary
 * 
 * 2017
 * 
 * Pin-out:
 * 
 * __8_____________1__
 * \ o * * * * * * o /
 *  \_o_*_*_o_*_*_o_/
 *   15           9
 *   
 *   1 - GND
 *   8 - DATA
 *   9 - CLOCK
 *   12- LATCH
 *   15- 5V
 *   
 *   Controler's protocol works as Shift register
 */
#include "Arduino.h"
#include <Joystick.h>
#include "NESController.h"

Joystick_ Joystick[2] = { Joystick_(3, JOYSTICK_TYPE_GAMEPAD, 6, 0, // Button Count, Hat Switch Count
		true, true, false,     // X and Y, but no Z Axis
		false, false, false,   // No Rx, Ry, or Rz
		false, false,          // No rudder or throttle
		false, false, false), Joystick_(4, JOYSTICK_TYPE_GAMEPAD, 6, 0, // Button Count, Hat Switch Count
		true, true, false,     // X and Y, but no Z Axis
		false, false, false,   // No Rx, Ry, or Rz
		false, false,          // No rudder or throttle
		false, false, false) };

const int DATA0_PIN = 8;
const int DATA1_PIN = 9;
const int LATCH_PIN = 7;
const int CLOCK_PIN = 4;

NESDriver driver = NESDriver(LATCH_PIN, CLOCK_PIN, DATA0_PIN, DATA1_PIN);

NESController* nes1 = driver.controller1();
NESController* nes2 = driver.controller2();

const int TICK = 16;

const int BTN_L1 = 10;
const int BTN_R1 = 16;
const int BTN_L2 = 14;
const int BTN_R2 = 15;

void setup() {
	pinMode(BTN_L1, INPUT_PULLUP);
	pinMode(BTN_R1, INPUT_PULLUP);
	pinMode(BTN_L2, INPUT_PULLUP);
	pinMode(BTN_R2, INPUT_PULLUP);

	driver.begin();

	Joystick[0].begin(false);
	Joystick[0].setXAxisRange(-1, 1);
	Joystick[0].setYAxisRange(-1, 1);

	Joystick[1].begin(false);
	Joystick[1].setXAxisRange(-1, 1);
	Joystick[1].setYAxisRange(-1, 1);
}

void loop() {
	driver.readControllers();
	int l1 = digitalRead(BTN_L1);
	int r1 = digitalRead(BTN_R1);
	int l2 = digitalRead(BTN_L2);
	int r2 = digitalRead(BTN_R2);
	updateJoystickState(Joystick[0], *nes1, l1==LOW, r1==LOW);
	updateJoystickState(Joystick[1], *nes2, l2==LOW, r2==LOW);
	delay(TICK);
}

bool updateJoystickState(Joystick_ Joystick, NESController nes, bool l, bool r) {
	if (nes.checkChanges()) {
		Joystick.setXAxis(nes.xAxis());
		Joystick.setYAxis(nes.yAxis());
		Joystick.setButton(0, nes.a());
		Joystick.setButton(1, nes.b());
		Joystick.setButton(2, nes.select());
		Joystick.setButton(3, nes.start());
		Joystick.setButton(4, l);
		Joystick.setButton(5, r);
		Joystick.sendState();
		return true;
	}
	return false;
}
