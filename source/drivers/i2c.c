#include <drivers/i2c.h>

void I2C_Init(I2C_Device* device, uint8_t slave_address) {
    TWSR = 0;
    TWBR = 32;
    device->slave_address = slave_address;
}

void I2C_Start(void) {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    _delay_ms(10);
}

void I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
