#include <game/Snake.h>


Snake::Snake(Adafruit_SSD1306* display, JoyInput* joystik, uint8_t buzzer)
    : Game(display, joystik, buzzer) {
    
    OnPreviewGame("Snake");
}

void Snake::OnInitGame() {
    is_running = true;

    head_snake = { static_cast<uint8_t>((display->width() / 2) / SIZE_CELL * SIZE_CELL), static_cast<uint8_t>((display->height() / 2) / SIZE_CELL * SIZE_CELL) };
    snake_size = 2;

    direction = RIGHT;
    
    snake_body[0] = { static_cast<uint8_t>(head_snake.x - SIZE_CELL * 1), head_snake.y };
    snake_body[1] = { static_cast<uint8_t>(head_snake.x - SIZE_CELL * 2), head_snake.y };

    sprintf(message_score, "score: %d", score);
    
    SpawnFruit();
}

void Snake::StartGame() {
    unsigned long update_time = 0;
    const unsigned long update_interval = 75;

    while (is_running) {
        unsigned long currentTime = millis();
        
        DetectCollision();

        display->clearDisplay();

            display->setCursor(0, 0);
            display->print(message_score);
            display->drawRect(0, SIZE_CELL, display->width(), display->height() - SIZE_CELL, WHITE);
            display->drawRect(head_snake.x, head_snake.y, SIZE_CELL, SIZE_CELL, WHITE);

            for (int i = snake_size - 1; i >= 0; --i) {
                display->fillRect(snake_body[i].x, snake_body[i].y, SIZE_CELL, SIZE_CELL, WHITE);
            }

            display->fillRect(fruit.x + (SIZE_CELL / 2 - 2), fruit.y, 4, SIZE_CELL, WHITE);
            display->fillRect(fruit.x, fruit.y + (SIZE_CELL / 2 - 2), SIZE_CELL, 4, WHITE);

        display->display();

        if (currentTime - update_time >= update_interval) {
            update_time = currentTime;

             if (direction == STOP) {
                 continue;
             }
             else if (joystik->Trigger(JoyInput::LEFT) && direction != RIGHT) {
                 direction = LEFT;
             }
             else if (joystik->Trigger(JoyInput::RIGHT) && direction != LEFT) {
                 direction = RIGHT;
             }
             else if (joystik->Trigger(JoyInput::UP) && direction != DOWN) {
                 direction = UP;
             }
             else if (joystik->Trigger(JoyInput::DOWN) && direction != UP) {
                 direction = DOWN;
            }

            if (direction != STOP) {
                for (int i = snake_size - 1; i > 0; --i) {
                    snake_body[i] = snake_body[i - 1];
                }
                snake_body[0] = head_snake;
            }

            if (direction == LEFT) {
                head_snake.x -= SIZE_CELL;
            }
            else if (direction == RIGHT) {
                head_snake.x += SIZE_CELL;
            }
            else if (direction == UP) {
                head_snake.y -= SIZE_CELL;
            }
            else if (direction == DOWN) {
                head_snake.y += SIZE_CELL;
            }
        }
    }

    OnGameOver(message_score);
}

void Snake::SpawnFruit() {
    fruit.x = static_cast<uint8_t>(RandomValue(SIZE_CELL, display->width() - SIZE_CELL) / SIZE_CELL * SIZE_CELL);
    fruit.y = static_cast<uint8_t>(RandomValue(SIZE_CELL, display->height() - SIZE_CELL) / SIZE_CELL * SIZE_CELL);
}

void Snake::EatFruit() {
    snake_size++;
    snake_body[snake_size - 1] = snake_body[snake_size - 2];
    sprintf(message_score, "score: %d", ++score);

    SpawnFruit();
    PlaySound();
}

void Snake::DetectCollision() {
    if (head_snake.x < fruit.x + SIZE_CELL && head_snake.x + SIZE_CELL > fruit.x && head_snake.y < fruit.y + SIZE_CELL && head_snake.y + SIZE_CELL > fruit.y) {
        EatFruit();
    }
    
    if (head_snake.x < 0 || head_snake.x > display->width() || head_snake.y < SIZE_CELL || head_snake.y > display->height()) {
        is_running = false;
    }
    for (int i = snake_size - 1; i >= 0; --i) {
        if (head_snake.x == snake_body[i].x && head_snake.y == snake_body[i].y) {
            is_running = false;
            return;
        }
    }
}