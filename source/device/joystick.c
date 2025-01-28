#include <device/joystick.h>


uint8_t joystick_yVR(uint8_t yVR_Pin) {
	return analog_Read(yVR_Pin);
}

uint8_t joystick_xVR(uint8_t xVR_Pin) {
	return analog_Read(xVR_Pin);
}

int joystick_pressed(uint8_t Btn_Pin) {
	return digital_Read(Btn_Pin) == LOW;
}