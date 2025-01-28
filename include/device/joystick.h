#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>
#include <util/delay.h>
#include <util/pin.h>

uint8_t joystick_yVR(uint8_t yVR_Pin);

uint8_t joystick_xVR(uint8_t xVR_Pin);

int joystick_pressed(uint8_t Btn_Pin);

#endif // JOYSTICK_H