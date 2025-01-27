#include <device/oled_SSD1306.h>


void OLED_Init(OLED_Display* display) {
    I2C_Start();
    I2C_Write(display->i2c_device.slave_address << 1);

    I2C_Write(SSD1306_DISPLAYOFF);
    I2C_Write(SSD1306_SETDISPLAYCLOCKDIV);
    I2C_Write(SSD1306_DEFAULT_CLOCKDIV);
    I2C_Write(SSD1306_SETMULTIPLEX);
    I2C_Write(SSD1306_DEFAULT_MULTIPLEX);
    I2C_Write(SSD1306_SETDISPLAYOFFSET);
    I2C_Write(SSD1306_DEFAULT_OFFSET);
    I2C_Write(SSD1306_SETSTARTLINE);
    I2C_Write(SSD1306_CHARGEPUMP);
    I2C_Write(SSD1306_CHARGE_PUMP_ON);
    I2C_Write(SSD1306_MEMORYMODE);
    I2C_Write(SSD1306_MEMORYMODE_HORIZONTAL);
    I2C_Write(SSD1306_SEGREMAP);
    I2C_Write(SSD1306_COMSCANDEC);
    I2C_Write(SSD1306_SETCOMPINS);
    I2C_Write(SSD1306_COM_PINS_CONFIG);
    I2C_Write(SSD1306_SETCONTRAST);
    I2C_Write(SSD1306_DEFAULT_CONTRAST);
    I2C_Write(SSD1306_DISPLAYALLON_RESUME);
    I2C_Write(SSD1306_NORMALDISPLAY);

    OLED_Fill(display, 0);

    I2C_Stop();
}

void OLED_Fill(OLED_Display* display, uint8_t color) {
    for (uint16_t i = 0; i < sizeof(display->buffer); i++) {
        display->buffer[i] = color ? 0xFF : 0x00;
    }
}

void OLED_Update(OLED_Display* display) {
    for (uint8_t page = 0; page < SCREEN_HEIGHT / 8; page++) {
        I2C_Start();
        I2C_Write(display->i2c_device.slave_address << 1);
        I2C_Write(0xB0 + page);
        I2C_Write(0x00);
        I2C_Write(0x10);

        for (uint16_t col = 0; col < SCREEN_WIDTH; col++) {
            I2C_Write(display->buffer[page * SCREEN_WIDTH + col]);
        }

        I2C_Stop();
    }
}