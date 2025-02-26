#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JoyInput.h>


class Game
{
public:
	Game(Adafruit_SSD1306* display, JoyInput* joystik) : display(display), joystik(joystik) {}
	~Game() = default;

	typedef struct coord {
		uint8_t x;
		uint8_t y;
	} coord;

protected:
	Adafruit_SSD1306* display = nullptr;
	JoyInput* joystik = nullptr;
	
	virtual bool OnInitGame() = 0;
	virtual void RenderGame() = 0;
	virtual void OnExitGame() = 0;
};