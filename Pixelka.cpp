#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <bitmap.h>
#include <Menu.h>
#include <JoyInput.h>
#include <game/snake.h>
#include <game/flappybird.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 2

#define BUZZER 9
#define GENERATOR A2



bool OnInitConsole();
void DrawMenu();
void HandleMenuSelection();

Menu menu;

JoyInput joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_BUTTON);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
    Serial.begin(9600);
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    else {
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);
    }
    
    display.clearDisplay();
    
        display.drawBitmap((SCREEN_WIDTH - pixelka_width) / 2, 10, pixelka, pixelka_width, pixelka_height, WHITE);
    
        display.setCursor(44, 55);
        display.println(F("Pixelka"));
    
    display.display();
    
    OnInitConsole();
    
    delay(3000);
}

void loop() {    
    DrawMenu();
    
    if (joystick.TriggerLeft() && menu.GetIndex() > 0) {
        menu.Prev();
        tone(BUZZER, 7500, 100);
        delay(200);
    }
    else if (joystick.TriggerRight() && menu.GetIndex() < menu.GetSize() - 1) {
        menu.Next();
        tone(BUZZER, 7500, 100);
        delay(200);
    }
    
    if (joystick.Pushbutton()) {
        HandleMenuSelection();
        delay(500);
    }
}

void DrawMenu() {
    int16_t x_pos, y_pos;
    uint16_t text_width, text_height;
    
    display.clearDisplay();
    
        const char* PROGMEM header = "Pixelka";
        display.setTextSize(2);
        display.getTextBounds(header, 0, 0, &x_pos, &y_pos, &text_width, &text_height);

        display.setCursor((display.width() - text_width) / 2, 0);
        display.println(header);

        display.setTextSize(1);
        display.getTextBounds(menu.GetSelection(), 0, 0, &x_pos, &y_pos, &text_width, &text_height);

        display.setCursor(0, (display.height() - text_height) / 2);
        if (menu.GetIndex() != 0) {
            display.print(F("<"));
        }

        display.setCursor((display.width() - text_width) / 2, (display.height() - text_height) / 2);
        display.print(menu.GetSelection());

        display.setCursor(122, (display.height() - text_height) / 2);
        if (menu.GetIndex() != menu.GetSize()) {
            display.print(F(">"));
        }

    display.display();
}

void HandleMenuSelection() {
    switch (menu.GetIndex()) {
        case 0: {         
            //Snake snake(&display, &joystick, BUZZER, GENERATOR);
            //snake.RenderGame();
            break;
        }
        case 1: {
            FlappyBird flappy_bird(&display, &joystick, BUZZER, GENERATOR);
            flappy_bird.RenderGame();
            break;
        }
        case 2: {
            break;
        }
    }
}

bool OnInitConsole() {
    pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);

    const char* PROGMEM option[3] = { "Snake", "Flappy bird", "Racer" };
    menu.AddOption(option[0]);
    menu.AddOption(option[1]);
    menu.AddOption(option[2]);

    return true;
}
