#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_Init();

uint8_t SPI_Transmit(uint8_t data);

#endif // SPI_H
