#pragma once

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <JoyInput.h>

#include <game/game.h>


class FlappyBird : Game {
private:

    typedef struct tube {
        coord position;
        uint8_t space;
    } tube;

    bool game_over = false;

    char message_score[16];
    uint8_t score = 0;
    coord bird = { 0, 0 };

    uint8_t height_space = 30;
    tube tube_first = { { 0, 0 }, 0 };

    uint8_t buzzer_pin = 0;
    uint8_t randomseed_pin = 0;

    void FlyTube();
    void SpawnTube();
    void DetectCollision();

public:
    FlappyBird(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin);

    bool OnInitGame();
    void RenderGame();
    void OnExitGame();
};