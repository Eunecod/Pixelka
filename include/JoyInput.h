#pragma once


typedef struct axis {
	int x;
	int y;
} axis;

class JoyInput {
private:
	int x_value;
	int y_value;

	uint8_t joystick_x			= -1;
	uint8_t joystick_y			= -1;
	uint8_t joystick_button		= -1;

public:
	JoyInput(uint8_t joystick_x, uint8_t joystick_y, uint8_t joystick_button);

	axis GetAxis();
	bool TriggerLeft();
	bool TriggerRight();
	bool TriggerUp();
	bool TriggerDown();
	bool Pushbutton();
};