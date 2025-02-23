#include <Arduino.h>
#include <JoyInput.h>


JoyInput::JoyInput(int joystick_x, int joystick_y, int joystick_button) 
	: joystick_x(joystick_x), joystick_y(joystick_y), joystick_button(joystick_button)
{}

axis JoyInput::GetAxis() {
	x_value = analogRead(joystick_x);
	y_value = analogRead(joystick_y);

	axis _axis;
	_axis.x = x_value;
	_axis.y = y_value;

	return _axis;
}

bool JoyInput::TriggerLeft() {
	x_value = analogRead(joystick_x);
	if (x_value < 300) {
		return true;
	}

	return false;
}

bool JoyInput::TriggerRight() {
	x_value = analogRead(joystick_x);
	if (x_value > 700) {
		return true;
	}

	return false;
}

bool JoyInput::TriggerUp() {
	y_value = analogRead(joystick_y);
	if (y_value > 700) {
		return true;
	}

	return false;
}

bool JoyInput::TriggerDown() {
	y_value = analogRead(joystick_y);
	if (y_value < 300) {
		return true;
	}

	return false;
}

bool JoyInput::Pushbutton() {
	return digitalRead(joystick_button) == LOW;
}
