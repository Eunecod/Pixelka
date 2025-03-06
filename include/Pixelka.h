#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Menu.h>
#include <JoyInput.h>

#include <bitmap.h>
#include <game/Snake.h>
#include <game/FlappyBird.h>
#include <game/DuckHunt.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 2

#define BUZZER 9


void DrawMenu();
void HandleMenuSelection();