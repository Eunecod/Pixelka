#ifndef PIN_H
#define PIN_H

#include <avr/io.h>
#include <util/delay.h>

#define HIGH 1
#define LOW 0

uint8_t analog_Read(uint8_t pin);

void analog_Write(uint8_t pin, uint8_t value);

int digital_Read(uint8_t pin);

void digital_Write(uint8_t pin, uint8_t value);

#endif // PIN_H