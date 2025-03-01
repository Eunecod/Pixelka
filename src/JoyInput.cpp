#include <Arduino.h>
#include <JoyInput.h>


JoyInput::JoyInput(const uint8_t joystick_x, const uint8_t joystick_y, const uint8_t joystick_button) 
	: joystick_x(joystick_x), joystick_y(joystick_y), joystick_button(joystick_button) {
	
	pinMode(joystick_x, INPUT);
	pinMode(joystick_y, INPUT);
	pinMode(joystick_button, INPUT_PULLUP);
}

axis JoyInput::GetAxis() const {
	return { analogRead(joystick_x), analogRead(joystick_y) };
}

bool JoyInput::Trigger(JoyInput::TRIGGER direction) const {
	switch (direction)
	{
	case JoyInput::LEFT:	
		return analogRead(joystick_x) < 100;

	case JoyInput::RIGHT:	
		return analogRead(joystick_x) > 900;

	case JoyInput::UP:		
		return analogRead(joystick_y) > 900;

	case JoyInput::DOWN:	
		return analogRead(joystick_y) < 100;

	default:
		return false;
	}
}

bool JoyInput::Push(bool use_debounce) {
	unsigned long current_time = millis();
	if (!use_debounce) {
		return digitalRead(joystick_button) == LOW;
	}

	if (digitalRead(joystick_button) == LOW) {
		if ((current_time - debounce_time) > DEBOUNCE) {
			debounce_time = current_time;

			return true;
		}
	}

	return false;
}