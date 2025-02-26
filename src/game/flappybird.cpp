#include <game/flappybird.h>


FlappyBird::FlappyBird(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin)
	: Game(display, joystik), buzzer_pin(buzzer_pin), randomseed_pin(randomseed_pin) {
    
    display->clearDisplay();
    display->setTextSize(1);
    if (!OnInitGame()) {
        display->setCursor(0, 0);
        display->println(F("Error: not init load game."));

        display->display();
        delay(1500);
    }

        int16_t x_pos, y_pos;
        uint16_t text_width, text_height;

        const char* title = "Flappy bird";
        display->getTextBounds(title, 0, 0, &x_pos, &y_pos, &text_width, &text_height);
        display->setCursor((display->width() - text_width) / 2, (display->height() - text_height) / 2);
        display->println(title);

    display->display();
    delay(1000);
}

void FlappyBird::DetectCollision() {
    if ((bird.y < tube_first.space || bird.y > tube_first.space + height_space) && (bird.x > tube_first.position.x && bird.x < tube_first.position.x + 5)) {
        game_over = true;
    }

    if (bird.y < 8 || bird.y >= display->height()) {
        game_over = true;
    }
}

void  FlappyBird::FlyTube() {
    ++score;
    sprintf(message_score, "score: %d", score);

    tone(buzzer_pin, 7500, 100);
}

void  FlappyBird::SpawnTube() {
    tube_first.position.x = display->width();
    tube_first.position.y = 8;

    tube_first.space = random(10, (display->height() - height_space) + 10);
}

bool FlappyBird::OnInitGame() {
    randomSeed(randomseed_pin);

    bird.x = 20;
    bird.y = display->height() / 2;

    sprintf(message_score, "score: %d", score);

    SpawnTube();

    return true;
}

void FlappyBird::RenderGame() {
    while (!game_over) {
        display->clearDisplay();

            display->setCursor(0, 0);
            display->print(message_score);

            display->drawRect(0, 8, display->width(), display->height() - 8, WHITE);
            display->fillRoundRect(bird.x, bird.y, 6, 6, 6, WHITE);

            display->fillRect(tube_first.position.x, tube_first.position.y, 5, tube_first.space, WHITE);
            display->fillRect(tube_first.position.x, tube_first.space + height_space, 5, display->height(), WHITE);

        display->display();

        if (joystik->Pushbutton()) {
            bird.y -= 7;
        }

        tube_first.position.x -= 7;
        if (tube_first.position.x > display->width()) {
            SpawnTube();
            FlyTube();
        }

        DetectCollision();

        bird.y += 2;
        delay(100);
    }

    OnExitGame();
}

void FlappyBird::OnExitGame() {
    int16_t x_pos, y_pos;
    uint16_t text_width, text_height;

    display->clearDisplay();

        const char* message = "GAME OVER";
        display->setTextSize(2);
        display->getTextBounds(message, 0, 0, &x_pos, &y_pos, &text_width, &text_height);
        display->setCursor((display->width() - text_width) / 2, 0);
        display->println(message);

        display->setTextSize(1);
        display->getTextBounds(message_score, 0, 0, &x_pos, &y_pos, &text_width, &text_height);
        display->setCursor((display->width() - text_width) / 2, (display->height() - text_height) / 2);
        display->println(message_score);

    display->display();

    delay(2000);
}
