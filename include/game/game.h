#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JoyInput.h>


class Game
{
public:
	Game(Adafruit_SSD1306* display, JoyInput* joystik) : display(display), joystik(joystik) {}
	~Game() = default;

protected:
	Adafruit_SSD1306* display = nullptr;
	JoyInput* joystik = nullptr;
	
	virtual bool OnInitGame() = 0;
	virtual void RenderGame() = 0;
	virtual void OnExitGame() = 0;
};