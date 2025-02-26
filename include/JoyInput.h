#pragma once


typedef struct axis {
	uint8_t x;
	uint8_t y;
} axis;

class JoyInput {
private:
	uint8_t x_value;
	uint8_t y_value;

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