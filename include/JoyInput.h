#ifndef JOYINPUT_H
#define JOYINPUT_H


typedef struct axis {
	int x;
	int y;
} axis;

class JoyInput {
private:
	int x_value;
	int y_value;

	int joystick_x			= -1;
	int joystick_y			= -1;
	int joystick_button		= -1;

public:
	JoyInput(int joystick_x, int joystick_y, int joystick_button);

	axis GetAxis();
	bool TriggerLeft();
	bool TriggerRight();
	bool TriggerUp();
	bool TriggerDown();
	bool Pushbutton();
	
protected:
};

#endif // JOYINPUT_H