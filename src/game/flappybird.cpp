#include <game/FlappyBird.h>


FlappyBird::FlappyBird(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer)
	: Game(display, joystik, buzzer) {
    
    OnPreviewGame("Flappy bird");
}

void FlappyBird::DetectCollision() {
    if ((bird.y - BIRD_RADIUS < tube_first.space || bird.y + BIRD_RADIUS > tube_first.space + height_space) && (bird.x > tube_first.position.x && bird.x < tube_first.position.x + BIRD_RADIUS)) {
        is_running = false;
    }
    
    if (bird.y < 8 || bird.y >= display->height()) {
        is_running = false;
    }
}

int FlappyBird::Clamp(int value, int min, int max) {
    return (value < min) ? min : (value > max) ? max : value;
}

void FlappyBird::FlyTube() {
    ++score;
    sprintf(message_score, "score: %d", score);
    
    PlaySound();
}

void FlappyBird::SpawnTube() {
    tube_first = { {static_cast<uint8_t>(display->width()), 8}, static_cast<uint8_t>(RandomValue(10, (display->height() - height_space) + 10)) };
}

bool FlappyBird::OnInitGame() {
    is_running = true;

    bird = { 20, static_cast<uint8_t>(display->height() / 2) };
    sprintf(message_score, "score: %d", score);
    
    SpawnTube();

    return true;
}

void FlappyBird::StartGame() {
    unsigned long update_time = 0;
    const unsigned long update_interval = 75;

    while (is_running) {
        unsigned long currentTime = millis();

        DetectCollision();

        display->clearDisplay();
        
            display->setCursor(0, 0);
            display->print(message_score);
        
            display->drawRect(0, 8, display->width(), display->height() - 8, WHITE);
            display->fillRoundRect(bird.x, bird.y, 6, 6, 6, WHITE);
        
            display->fillRect(tube_first.position.x, tube_first.position.y, TUBE_WIDTH, tube_first.space, WHITE);
            display->fillRect(tube_first.position.x, tube_first.space + height_space, TUBE_WIDTH, display->height(), WHITE);
        
        display->display();
        
        if (currentTime - update_time >= update_interval) {
            update_time = currentTime;

            if (joystik->Push(false)) {
                bird.y -= 5;
            }

            tube_first.position.x -= 3;
            if (tube_first.position.x > display->width()) {
                SpawnTube();
                FlyTube();
            }

            bird.y += 2;
        }        
    }

    OnGameOver(message_score);
}
