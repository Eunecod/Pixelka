#pragma once

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <JoyInput.h>

#include <game/game.h>


class DuckHunt : Game {
    
    axis velocity;
    const int neutral = 512;
    const int threshold = 350;

    coord crosshair = { 0, 0 };
    coord bird = { 0, 0 };

    char message_score[16];
    uint8_t score = 0;
    uint8_t pass;

    void DetectCollision();
    void SpawnBird();
    void Shoot();

public:
    DuckHunt(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer);

    bool OnInitGame();
    void StartGame();
};