#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <drivers/i2c.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SSD1306_DISPLAYOFF              0xAE
#define SSD1306_SETDISPLAYCLOCKDIV      0xD5
#define SSD1306_SETMULTIPLEX            0xA8
#define SSD1306_SETDISPLAYOFFSET        0xD3
#define SSD1306_SETSTARTLINE            0x40
#define SSD1306_CHARGEPUMP              0x8D
#define SSD1306_MEMORYMODE              0x20
#define SSD1306_SEGREMAP                0xA1
#define SSD1306_COMSCANDEC              0xC8
#define SSD1306_SETCOMPINS              0xDA
#define SSD1306_SETCONTRAST             0x81
#define SSD1306_DISPLAYALLON_RESUME     0xA4
#define SSD1306_NORMALDISPLAY           0xA6
#define SSD1306_DEFAULT_CLOCKDIV        0x80 
#define SSD1306_DEFAULT_MULTIPLEX       (SCREEN_HEIGHT - 1) 
#define SSD1306_DEFAULT_OFFSET          0x00 
#define SSD1306_CHARGE_PUMP_ON          0x14
#define SSD1306_MEMORYMODE_HORIZONTAL   0x00
#define SSD1306_COM_PINS_CONFIG         0x12
#define SSD1306_DEFAULT_CONTRAST        0x7F

typedef struct {
    I2C_Device i2c_device;
    uint8_t buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];
} OLED_Display;

void OLED_Init(OLED_Display* display);

void OLED_Fill(OLED_Display* display, uint8_t color);

void OLED_Update(OLED_Display* display);

#endif // OLED_SSD1306_H