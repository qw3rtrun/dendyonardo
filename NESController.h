#ifndef NESCONTROLLER_h
#define NESCONTROLLER_h

struct ControllerState{
	int xAxis = 0;
	int yAxis = 0;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool start = false;
	bool select = false;
	bool a = false;
	bool b = false;
} ;

class NESDriver {
	public:
		NESDriver(int latchPin, int clockPin);
		void begin();
		ControllerState read(int dataPin);
		void update(int dataPins[], ControllerState states[]);
	private:
		int _latchPin;
		int _clockPin;
};

#endif
