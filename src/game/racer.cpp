#include <game/racer.h>


Racer::Racer(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin)
    : Game(display, joystik), buzzer_pin(buzzer_pin), randomseed_pin(randomseed_pin) {

}

void Racer::DetectCollision() {

}

void Racer::RenderGame() {

}

bool Racer::OnInitGame() {

}

void Racer::OnExitGame() {

}
