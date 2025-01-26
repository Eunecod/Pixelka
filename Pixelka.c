#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define UBRR (F_CPU / 16 / BAUD - 1)


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

int main() {
    USART_Init(UBRR);
    USART_SendString("Hello, Arduino!\r\n");

    return 0;
}
