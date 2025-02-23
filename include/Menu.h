#ifndef MENU_H
#define MENU_H

#define STACK_MENU 32


class Menu {
private:
	int menu_size = 0;
	int menu_index = 0;
	const char* menu_items[STACK_MENU] = { nullptr };

public:
	Menu();
	void AddOption(const char* option);
	bool Next();
	bool Prev();
	
	const char* GetSelection();
	int GetIndex();
	int GetSize();

protected:
};

#endif // MENU_H