#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define SLAVE_ADDRESS 0x33

typedef struct {
    uint8_t slave_address;
} I2C_Device;

void I2C_Init(I2C_Device* device);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(uint8_t data);

#endif // I2C_H