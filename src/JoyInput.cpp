#include <Arduino.h>
#include <JoyInput.h>


//namespace JoyInput {
//
//	axis GetAxis(uint8_t joystick_x, uint8_t joystick_y) {
//		axis _axis = { analogRead(joystick_x), analogRead(joystick_y) };
//		return _axis;
//	}
//
//	bool TriggerLeft(uint8_t joystick_x) {
//		if (analogRead(joystick_x) < 300) {
//			return true;
//		}
//
//		return false;
//	}
//
//	bool TriggerRight(uint8_t joystick_x) {
//		if (analogRead(joystick_x) > 700) {
//			return true;
//		}
//
//		return false;
//	}
//
//	bool TriggerUp(uint8_t joystick_y) {
//		if (analogRead(joystick_y) > 700) {
//			return true;
//		}
//
//		return false;
//	}
//
//	bool TriggerDown(uint8_t joystick_y) {
//		if (analogRead(joystick_y) < 300) {
//			return true;
//		}
//
//		return false;
//	}
//
//	bool Pushbutton(uint8_t joystick_button) {
//		return digitalRead(joystick_button) == LOW;
//	}
//
//} // JoyInput

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
	case JoyInput::LEFT:	return analogRead(joystick_x) < 100;
	case JoyInput::RIGHT:	return analogRead(joystick_x) > 900;
	case JoyInput::UP:		return analogRead(joystick_y) < 100;
	case JoyInput::DOWN:	return analogRead(joystick_y) > 900;
		default:
			return false;
	}
}

bool JoyInput::Push() const {
	return digitalRead(joystick_button) == LOW;
}