#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <JoyInput.h>

#include <game/game.h>


class Snake : Game {
private:
	typedef struct coord {
		uint8_t x;
		uint8_t y;
	} coord;

    enum DIRECTION : uint8_t {
        STOP = 0, LEFT, RIGHT, UP, DOWN
    } direction;
    
    bool game_over = false;
    
    char message_score[16];
    uint8_t score = 0;
    coord fruit = { 0, 0 };

    coord head_snake = { 0, 0 };
    coord snake_body[32];
    uint8_t snake_size = 0;

    uint8_t buzzer_pin = 0;
    uint8_t randomseed_pin = 0;

    void EatFruit();
    void SpawnFruit();
    void DetectCollision();
    
public:
    Snake(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin);
    
	bool OnInitGame();
	void RenderGame();
	void OnExitGame();
};