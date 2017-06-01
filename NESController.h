#ifndef NESCONTROLLER_h
#define NESCONTROLLER_h

#define A 0x80
#define B 0x40
#define SELECT 0x20
#define START 0x10
#define UP 0x04
#define DOWN 0x08
#define LEFT 0x02
#define RIGHT 0x01

class NESController {
	public:
		NESController(int dataPin);
		bool isConnected();
		bool checkChanges();
		int xAxis();
		int yAxis();
		bool up();
		bool down();
		bool left();
		bool right();
		bool start();
		bool select();
		bool a();
		bool b();
	protected:
		void read(int i);
	private:
		bool button(int mask);
		int _dataPin;
		byte _state;
		byte _previousState;
};

class NESDriver {
	public:
		NESDriver(int latchPin, int clockPin, int dataPin);
		NESDriver(int latchPin, int clockPin, int dataPin1, int datePin2);
		void begin();
		void readControllers();
		NESController controller1();
		NESController controller2();
	private:
		int _latchPin;
		int _clockPin;
		int _count;
		NESController _cs[];
};

#endif
