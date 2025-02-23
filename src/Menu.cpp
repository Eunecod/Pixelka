#include <Menu.h>


Menu::Menu() {}

void Menu::AddOption(const char* option) {
	if (menu_size == STACK_MENU) {
		return;
	}

	menu_items[menu_size] = option;
	++menu_size;
}

bool Menu::Next() {
	if (menu_index < menu_size - 1) {
		++menu_index;
		return true;
	}

	return false;
}

bool Menu::Prev() {
	if (menu_index != 0) {
		--menu_index;
		return true;
	}

	return false;
}

const char* Menu::GetSelection() {
	return menu_items[menu_index];
}

int Menu::GetIndex() {
	return menu_index;
}

int Menu::GetSize() {
	return menu_size - 1;
}