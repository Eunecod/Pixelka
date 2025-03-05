#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>


class Menu {

	static constexpr uint8_t size = 5;
	static const char* const items[];
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
