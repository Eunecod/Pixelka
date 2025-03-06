#include <Pixelka.h>


Menu menu;
JoyInput joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_BUTTON);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
    Serial.begin(9600);
    pinMode(BUZZER, OUTPUT); 
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.clearDisplay();
    
        display.drawBitmap((SCREEN_WIDTH - pixelka_width) / 2, 10, pixelka, pixelka_width, pixelka_height, WHITE);
    
        display.setCursor(44, 55);
        display.println(F("Pixelka"));
    
    display.display();

    delay(1500);
}

static unsigned long trigger_time = 0;
const unsigned long trigger_timeout = 200;
void loop() {   
    unsigned long current_time = millis();

    if (joystick.Trigger(JoyInput::LEFT) && current_time - trigger_time >= trigger_timeout) {
        menu.Prev();
        tone(BUZZER, 7500, 100);
        trigger_time = current_time;
    }
    else if (joystick.Trigger(JoyInput::RIGHT) && current_time - trigger_time >= trigger_timeout) {
        menu.Next();
        tone(BUZZER, 7500, 100);
        trigger_time = current_time;
    }

    if (joystick.Push()) {
        HandleMenuSelection();
    }

    DrawMenu();

    static unsigned long display_update = 0;
    if (current_time - display_update >= 50) {
        display_update = current_time;
    }
}

void DrawMenu() {
    uint16_t text_width, text_height;
    
    display.clearDisplay();
    
        const char* header PROGMEM = "Pixelka";
        display.setTextSize(2);
        display.getTextBounds(header, 0, 0, nullptr, nullptr, &text_width, &text_height);
        
        display.setCursor((display.width() - text_width) / 2, 0);
        display.println(header);
        
        display.setTextSize(1);
        display.getTextBounds(menu.GetItems(), 0, 0, nullptr, nullptr, &text_width, &text_height);
        
        display.setCursor(0, (display.height() - text_height) / 2);
        if (menu.GetIndex() != 0) {
            display.print(F("<"));
        }

        display.setCursor((display.width() - text_width) / 2, (display.height() - text_height) / 2);
        display.print(menu.GetItems());

        display.setCursor(122, (display.height() - text_height) / 2);
        if (menu.GetIndex() != menu.GetSize() - 1) {
            display.print(F(">"));
        }

    display.display();
}

void HandleMenuSelection() {
    switch (menu.GetIndex()) {
        case 0: {      
            Snake snake(&display, &joystick, BUZZER);
            snake.OnInitGame();
            snake.StartGame();

            break;
        }
        case 1: {
            FlappyBird flappy_bird(&display, &joystick, BUZZER);
            flappy_bird.OnInitGame();
            flappy_bird.StartGame();

            break;
        }
        case 2: {
            DuckHunt duck_hunt(&display, &joystick, BUZZER);
            duck_hunt.OnInitGame();
            duck_hunt.StartGame();

            break;
        }
        case 4: {
            display.clearDisplay();
            
                display.drawBitmap((SCREEN_WIDTH - qrcode_width) / 2, 0, qrcode, qrcode_width, qrcode_height, WHITE);
            
            display.display();
            do {
            } while (!joystick.Push());

            break;
        }
    }
}
