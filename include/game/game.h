#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <JoyInput.h>


typedef struct coord {
	uint8_t x;
	uint8_t y;
} coord;

class Game
{
public:
	Game(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer) 
		: display(display), joystik(joystik), buzzer(buzzer) {};
	~Game() = default;

protected:
	Adafruit_SSD1306* display;
	JoyInput* joystik;
	uint8_t buzzer;

	bool is_running;

	inline void PlaySound() {
		tone(buzzer, 7500, 100);
	}

	inline long RandomValue(long min, long max) {
		randomSeed(analogRead(micros()));
		return random(min, max);
	}

	inline void OnPreviewGame(const char* title) {
		uint16_t text_width, text_height;

		display->clearDisplay();

			display->setTextSize(1);
			display->getTextBounds(title, 0, 0, nullptr, nullptr, &text_width, &text_height);
			display->setCursor((display->width() - text_width) / 2, (display->height() - text_height) / 2);
			display->println(title);

		display->display();

		delay(1000);
	}

	inline void OnGameOver(char* score) {
		uint16_t text_width, text_height;

		display->clearDisplay();

			const char* title PROGMEM = "GAME OVER";
			display->setTextSize(2);
			display->getTextBounds(title, 0, 0, nullptr, nullptr, &text_width, &text_height);
			display->setCursor((display->width() - text_width) / 2, 0);
			display->println(title);

			display->setTextSize(1);
			display->getTextBounds(score, 0, 0, nullptr, nullptr, &text_width, &text_height);
			display->setCursor((display->width() - text_width) / 2, (display->height() - text_height) / 2);
			display->println(score);

		display->display();

		delay(2000);
	}
};