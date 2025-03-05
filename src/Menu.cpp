#include <menu.h>


const char* const Menu::items[] PROGMEM = { "Snake", "Flappy bird", "Duck hunt", "Leader board", "GitHub" };

void Menu::Next() {
	if (index < size - 1) {
		index++;
	}
}

void Menu::Prev() {
	if (index > 0) {
		index--;
	}
}

const char* Menu::GetItems() const {
	return items[index];
}

int8_t Menu::GetIndex() const {
	return index;
}

int8_t Menu::GetSize() const {
	return size;
}