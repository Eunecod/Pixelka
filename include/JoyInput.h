#pragma once


typedef struct axis {
	int x;
	int y;
} axis;

class JoyInput {
	
	uint8_t joystick_x;
	uint8_t joystick_y;
	uint8_t joystick_button;

public:
	JoyInput(const  uint8_t joystick_x, const  uint8_t joystick_y, const  uint8_t joystick_button);
	~JoyInput() = default;

	enum TRIGGER : uint8_t {
		LEFT, RIGHT, UP, DOWN,
	};

	axis GetAxis() const;
	bool Trigger(TRIGGER direction) const;
	bool Push() const;

};