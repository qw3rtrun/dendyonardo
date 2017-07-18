#ifndef NESJOYADAPTER_h
#define NESJOYADAPTER_h

#include <Joystick.h>

class NESAdapter {
private:
	Joystick_ joy;
	bool changed;
	int x, y;
	bool a, b, start, select, l, r;
public:
	NESAdapter(int joyId);
	void begin();
	void reset();
	void setA(bool pushed);
	void setB(bool pushed);
	void setStart(bool pushed);
	void setSelect(bool pushed);
	void setY(int y);
	void setX(int x);
	void setL(bool pushed);
	void setR(bool pushed);
	void sendState();
};

#endif
