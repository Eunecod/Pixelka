#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <bitmap.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 2


int menu_index = 0;
const char* menu_items[] = { "Snake", "Floppy bird", "Racer" };
const int menu_size = 3;

void DrawMenu();
void HandleMenuSelection(int index);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
    Serial.begin(9600);
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    else {
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
    }

    display.clearDisplay();
    
    display.drawBitmap(0, 0, pixelka, pixelka_width, pixelka_height, WHITE);
    display.display();
    delay(5000);

    display.clearDisplay();

    pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
}

void loop() {
    int x_value = analogRead(JOYSTICK_X);
    int y_value = analogRead(JOYSTICK_Y);
    bool button_pressed = digitalRead(JOYSTICK_BUTTON) == LOW;

    if (x_value < 300 && menu_index > 0) {
        menu_index--;
        delay(200);
    }
    else if (x_value > 700 && menu_index < menu_size - 1) {
        menu_index++;
        delay(200);
    }

    if (button_pressed) {
        HandleMenuSelection(menu_index);
        delay(500);
    }

    DrawMenu();
}

void DrawMenu() {
    int16_t x_pos;
    int16_t y_pos;
    uint16_t text_width;
    uint16_t text_height;

    const char* header = "Pixelka";
    display.getTextBounds(header, 0, 0, &x_pos, &y_pos, &text_width, &text_height);

    display.clearDisplay();
    display.setCursor((SCREEN_WIDTH - text_width) / 2, 0);
    display.println(header);

    display.getTextBounds(menu_items[menu_index], 0, 0, &x_pos, &y_pos, &text_width, &text_height);

    display.setCursor(0, (SCREEN_HEIGHT - text_height) / 2);
    if (menu_index != 0) {
        display.print("<");
    }

    display.setCursor((SCREEN_WIDTH - text_width) / 2, (SCREEN_HEIGHT - text_height) / 2);
    display.print(menu_items[menu_index]);

    display.setCursor(122, (SCREEN_HEIGHT - text_height) / 2);
    if (menu_index != menu_size - 1) {
        display.print(">");
    }

    display.display();
}

void HandleMenuSelection(int index) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(menu_items[index]);
    display.display();
    delay(1000);

    switch (index) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }
}
