#include <game/DuckHunt.h>


DuckHunt::DuckHunt(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer)
    : Game(display, joystik, buzzer) {
    
    OnPreviewGame("Duck hunt");
}

void DuckHunt::StartGame() {

    while (is_running) {
        velocity = joystik->GetAxis();
        
        DetectCollision();

        display->clearDisplay();
            
            display->setCursor(0, 0);
            display->print(message_score);
            display->drawRect(0, 8, display->width(), display->height() - 8, WHITE);

            display->drawCircle(crosshair.x, crosshair.y, 6, WHITE);
            display->drawLine(crosshair.x - 8, crosshair.y, crosshair.x + 8, crosshair.y, WHITE);
            display->drawLine(crosshair.x, crosshair.y - 8, crosshair.x, crosshair.y + 8, WHITE);
        
            display->fillRect(bird.x, bird.y, 10, 10, WHITE);
        
        display->display();

        if (velocity.x > neutral + threshold) {
            crosshair.x += 5;
        }
        else if (velocity.x < neutral - threshold) {
            crosshair.x -= 5;
        }

        if (velocity.y > neutral + threshold) {
            crosshair.y -= 5;
        }
        else if (velocity.y < neutral - threshold) {
            crosshair.y += 5;
        }

        if (joystik->Push()) {
            Shoot();
        }
    
        bird.x += 1;
    }

    OnGameOver(message_score);
}

void DuckHunt::DetectCollision() {
    if (bird.x > display->width() + 30) {
        --pass;
        if (pass <= 0) {
            is_running = false;
            
            return;
        }
        SpawnBird();
    }
}

void DuckHunt::Shoot() {
    if (bird.x < crosshair.x && bird.x + 10 > crosshair.x && bird.y < crosshair.y && bird.y + 10 > crosshair.y) {
        ++score;
        sprintf(message_score, "score: %d", score);
        
        SpawnBird();
    }
    PlaySound();
}

void DuckHunt::SpawnBird() {
    bird = { 0, static_cast<uint8_t>(RandomValue(8, display->height() - 8)) };
}

bool DuckHunt::OnInitGame() {
    is_running = true;

    pass = 3;
    crosshair = { static_cast<uint8_t>(display->width() / 2), static_cast<uint8_t>(display->height() / 2) };

    sprintf(message_score, "score: %d", score);

    SpawnBird();

    return true;
}
