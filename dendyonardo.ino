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
#include <Joystick.h>

Joystick_ Joystick[2] = {
  Joystick_(3,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false),
  Joystick_(4,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false)
};

const int DATA0_PIN = 2;
const int DATA1_PIN = 5;
const int LATCH_PIN = 3;
const int CLOCK_PIN = 4;

const int TICK = 16;

const int A = 0x80;
const int B = 0x40;
const int SELECT = 0x20;
const int START = 0x10;
const int UP = 0x04;
const int DOWN = 0x08;
const int LEFT = 0x02;
const int RIGHT = 0x01;

int lastState0 = 0xFF;
int lastState1 = 0xFF;

void setup() {
  pinMode(DATA0_PIN, INPUT);
  pinMode(DATA1_PIN, INPUT);
  
  pinMode(LATCH_PIN, OUTPUT);
  digitalWrite(LATCH_PIN, LOW);

  pinMode(CLOCK_PIN, OUTPUT);
  digitalWrite(CLOCK_PIN, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Joystick[0].begin(false);
  Joystick[0].setXAxisRange(-1, 1);
  Joystick[0].setYAxisRange(-1, 1);

  Joystick[1].begin(false);
  Joystick[1].setXAxisRange(-1, 1);
  Joystick[1].setYAxisRange(-1, 1);
}

void loop() {
  digitalWrite(LATCH_PIN, HIGH);
    delay(TICK);
    digitalWrite(LATCH_PIN, LOW);
    delay(TICK / 2);
    int state = shiftRead();

    int state0 = state &0xFF;
    if (state0 == 0) {
      state0 = 0xFF;
    }
    int state1 = (state >> 8) & 0xFF;
    if (state1 == 0) {
      state1 = 0xFF;
    }

    digitalWrite(LED_BUILTIN, (state0 & state1) != 0xFF );
    if (lastState0 != state0) {
      updateJoystickState(Joystick[0], state0);
      lastState0 = state0;
    }
    if (lastState1 != state1) {
      updateJoystickState(Joystick[1], state1);
      lastState1 = state1;
    }

    delay(TICK);
}

void updateJoystickState(Joystick_ Joystick, byte state) {
  Joystick.setXAxis(getAxis(state, RIGHT, LEFT));
  Joystick.setYAxis(getAxis(state, UP, DOWN));
  Joystick.setButton(0, getButton(state, A));
  Joystick.setButton(1, getButton(state, B));
  Joystick.setButton(2, getButton(state, SELECT));
  Joystick.setButton(3, getButton(state, START));
  Joystick.sendState();
}


