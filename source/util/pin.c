#include <util/pin.h>


uint8_t analog_Read(uint8_t pin) {
    ADMUX = (1 << REFS0) | pin;
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); 

    ADMUX = (ADMUX & 0xF8) | (pin & 0x07);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADC / 4;
}

void analog_Write(uint8_t pin, uint8_t value) {}

int digital_Read(uint8_t pin) {
    uint8_t bit = pin % 8;

    if (PINB & (1 << bit)) {
        return HIGH;
    }
    else {
        return LOW;
    }
}

void digital_Write(uint8_t pin, uint8_t value) {
    uint8_t bit = pin % 8;

    if (value == HIGH) {
        PORTB |= (1 << bit);
    }
    else {
        PORTB &= ~(1 << bit);
    }
}