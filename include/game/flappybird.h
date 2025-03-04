#pragma once
#include <game/Game.h>

#define TUBE_WIDTH 5
#define BIRD_RADIUS 6


class FlappyBird : Game {

    typedef struct tube {
        coord position;
        uint8_t space;
    } tube;

    char message_score[16];
    uint8_t score = 0;
    coord bird = { 0, 0 };

    uint8_t height_space = 30;
    tube tube_first = { { 0, 0 }, 0 };

    void FlyTube();
    void SpawnTube();
    void DetectCollision();
    int Clamp(int value, int min, int max);

public:
    FlappyBird(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer);
    ~FlappyBird() = default;

    bool OnInitGame();
    void StartGame();
};