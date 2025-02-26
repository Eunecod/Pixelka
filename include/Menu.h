#pragma once
#include <Arduino.h>

#define STACK_MENU 3


class Menu {
private:
	int8_t menu_size = 0;
	int8_t menu_index = 0;
	const char* menu_items[STACK_MENU];

public:
	Menu();
	void AddOption(const char* option);
	bool Next();
	bool Prev();
	
	const char* GetSelection();
	int8_t GetIndex();
	int8_t GetSize();
};