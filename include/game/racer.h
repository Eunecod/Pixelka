#pragma once

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <JoyInput.h>

#include <game/game.h>


class Racer : Game {
private:

    bool game_over = false;

    char message_score[16];
    uint8_t score = 0;

    uint8_t buzzer_pin = 0;
    uint8_t randomseed_pin = 0;

    void DetectCollision();

public:
    Racer(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin);

    bool OnInitGame();
    void RenderGame();
    void OnExitGame();
};