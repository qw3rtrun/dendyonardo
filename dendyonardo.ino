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
#include "NESAdapter.h"

const int DATA0_PIN = 8;
const int DATA1_PIN = 9;
const int LATCH_PIN = 7;
const int CLOCK_PIN = 4;
const int BTN_L1 = 10;
const int BTN_R1 = 16;
const int BTN_L2 = 14;
const int BTN_R2 = 15;
const int LED_1 = 5;
const int LED_2 = 6;

NESDriver driver = NESDriver(LATCH_PIN, CLOCK_PIN, DATA0_PIN, DATA1_PIN);
NESController* nes1 = driver.controller1();
NESController* nes2 = driver.controller2();

NESAdapter joy1 = NESAdapter(3);
NESAdapter joy2 = NESAdapter(4);

const int TICK = 16;

void setup() {
	pinMode(BTN_L1, INPUT_PULLUP);
	pinMode(BTN_R1, INPUT_PULLUP);
	pinMode(BTN_L2, INPUT_PULLUP);
	pinMode(BTN_R2, INPUT_PULLUP);
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	digitalWrite(LED_1, LOW);
	digitalWrite(LED_2, LOW);

	driver.begin();

	joy1.begin();
	joy2.begin();
}

void loop() {
	driver.readControllers();
	int l1 = digitalRead(BTN_L1);
	int r1 = digitalRead(BTN_R1);
	int l2 = digitalRead(BTN_L2);
	int r2 = digitalRead(BTN_R2);
	digitalWrite(LED_1,
			updateJoystickState(joy1, *nes1, l1 == LOW, r1 == LOW));
	digitalWrite(LED_2,
			updateJoystickState(joy2, *nes2, l2 == LOW, r2 == LOW));
	delay(TICK);
}

bool updateJoystickState(NESAdapter joy, NESController nes, bool l, bool r) {
	if (nes.isConnected()) {
		joy.setX(nes.xAxis());
		joy.setY(nes.yAxis());
		joy.setA(nes.a());
		joy.setB(nes.b());
		joy.setSelect(nes.select());
		joy.setStart(nes.start());
		joy.setL(l);
		joy.setR(r);
		joy.sendState();
		return true;
	} else {
		joy.reset();
		joy.sendState();
		return false;
	}

}

