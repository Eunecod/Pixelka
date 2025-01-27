#include <util/delay.h>
#include <drivers/i2c.h>
#include <device/oled_SSD1306.h>

#define BAUD 9600
#define UBRR (F_CPU / 16 / BAUD - 1)

I2C_Device myDevice;
OLED_Display display;

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_SendString(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

void setup(void) {
    USART_Init(UBRR);
    USART_SendString("Start...\r\n");
    USART_SendString("Start I2C Init...\r\n");
    I2C_Init(&myDevice, 0x3D);
    USART_SendString("End I2C Init...\r\n");

    USART_SendString("Start Oled Init...\r\n");
    display.i2c_device.slave_address = myDevice.slave_address;
    OLED_Init(&display);
    USART_SendString("End Oled Init...\r\n");

    OLED_Fill(&display, 1);
    OLED_Update(&display);
    
    USART_SendString("End setup...\r\n");
    _delay_ms(1000); 
}

void loop(void) {
    USART_SendString("Fill Black...\r\n");
    _delay_ms(1000);
    OLED_Fill(&display, 0);
    OLED_Update(&display);

    USART_SendString("Fill White...\r\n");
    _delay_ms(1000);
    OLED_Fill(&display, 1);
    OLED_Update(&display);

    USART_SendString("Loop...\r\n");
}

int main() {
    setup();

    for (;;) {
        loop();
    }

    return 0;
}