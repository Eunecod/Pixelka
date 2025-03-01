#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>


class Menu {

	static constexpr uint8_t size = 5;
	const char* items[size] PROGMEM = { "Snake", "Flappy bird", "Duck hunt", "Leader board", "GitHub"};
	int8_t index = 0;

public:
	Menu() = default;
	~Menu() = default;

	void Next();
	void Prev();
	
	const char* GetItems() const;
	int8_t GetIndex() const;
	int8_t GetSize() const;
};