#include <game/snake.h>


Snake::Snake(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer_pin, uint8_t randomseed_pin)
    : Game(display, joystik), buzzer_pin(buzzer_pin), randomseed_pin(randomseed_pin) {
    if (!OnInitGame()) {
        display->clearDisplay();

            display->setTextSize(1);
            display->setCursor(0, 0);
            display->println(F("Error: not init load game."));

        display->display();
        delay(1500);
    }
}

bool Snake::OnInitGame() {
    randomSeed(randomseed_pin);

    head_snake = { display->width() >> 1 , display->height() >> 1 };

    snake_body[0] = { head_snake.x - 6 * 1, head_snake.y };
    snake_body[1] = { head_snake.x - 6 * 2, head_snake.y };
    snake_body[2] = { head_snake.x - 6 * 3, head_snake.y };

    snake_size = 3;

    SpawnFruit();

    sprintf(message_score, "score: %d", score);

    direction = RIGHT;

    return true;
}

void Snake::RenderGame() {
    while (!game_over) {
        display->clearDisplay();

            display->setCursor(0, 0);
            display->print(message_score);

            display->drawRect(0, 8, display->width(), display->height() - 8, WHITE);
            display->fillRect(head_snake.x, head_snake.y, 6, 6, WHITE);
            for (int i = 0; i < snake_size - 1; ++i) {
                display->fillRect(snake_body[i].x, snake_body[i].y, 6, 6, WHITE);
            }

            display->drawRect(fruit.x, fruit.y, 6, 6, WHITE);

        display->display();

        if (joystik->TriggerLeft() && direction != RIGHT) {
            direction = LEFT;
        }
        else if (joystik->TriggerRight() && direction != LEFT) {
            direction = RIGHT;
        }
        else if (joystik->TriggerUp() && direction != DOWN) {
            direction = UP;
        }
        else if (joystik->TriggerDown() && direction != UP) {
            direction = DOWN;
        }

        for (int i = snake_size - 1; i > 0; --i) {
            snake_body[i].x = snake_body[i - 1].x;
            snake_body[i].y = snake_body[i - 1].y;
        }

        snake_body[0].x = head_snake.x;
        snake_body[0].y = head_snake.y;

        if (direction == LEFT) {
            head_snake.x -= 6;
        }
        else if (direction == RIGHT) {
            head_snake.x += 6;
        }
        else if (direction == UP) {
            head_snake.y -= 6;
        }
        else if (direction == DOWN) {
            head_snake.y += 6;
        }

        DetectCollision();
        delay(100);
    }

    OnExitGame();
}

void Snake::OnExitGame() {
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

void Snake::SpawnFruit() {
    fruit.x = random(8, display->width() - 8);
    fruit.y = random(8, display->height() - 8);
}

void Snake::EatFruit() {
    ++score;
    ++snake_size;
    snake_body[snake_size].x = snake_body[snake_size - 1].x;
    snake_body[snake_size].y = snake_body[snake_size - 1].y;

    sprintf(message_score, "score: %d", score);

    SpawnFruit();
    tone(buzzer_pin, 7500, 100); 
}

void Snake::DetectCollision() {
    if (head_snake.x < fruit.x + 6 && head_snake.x + 6 > fruit.x && head_snake.y < fruit.y + 6 && head_snake.y + 6 > fruit.y) {
        EatFruit();
    }

    if (head_snake.x < 0 || head_snake.x > display->width() || head_snake.y < 8 || head_snake.y > display->height() - 8) {
        game_over = true;
    }
    for (int i = snake_size - 1; i >= 0; --i) {
        if (head_snake.x == snake_body[i].x && head_snake.y == snake_body[i].y) {
            game_over = true;
            return;
        }
    }

    if (head_snake.x < 0 || head_snake.x > display->width() || head_snake.y < 8 || head_snake.y > display->height() - 8) {
        game_over = true;
    }
}