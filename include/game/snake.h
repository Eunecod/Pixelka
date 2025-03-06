#pragma once
#include <game/Game.h>

#define SIZE_CELL 8


class Snake : Game {

    enum DIRECTION : uint8_t {
        STOP = 0, LEFT, RIGHT, UP, DOWN
    } direction;
    
    char message_score[16];
    uint8_t score = 0;
    coord fruit = { 0, 0 };

    coord head_snake = { 0, 0 };
    coord snake_body[64];
    uint8_t snake_size = 0;

    void EatFruit();
    void SpawnFruit();
    void DetectCollision();
    
public:
    Snake(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer);
    ~Snake() = default;

	void OnInitGame();
	void StartGame();
	void OnExitGame();
};