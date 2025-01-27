#include <util/delay.h>
#include <drivers/i2c.h>


void setup(void) {
    I2C_Device myDevice;
    I2C_Init(&myDevice);

    I2C_Start();
    I2C_Write(myDevice.slave_address << 1);
    I2C_Write(0x31);
    I2C_Write(0x41);
    I2C_Stop();
    
    _delay_ms(1000); 
}

void loop(void) {
}

int main() {
    setup();

    for (;;) {
        loop();
    }

    return 0;
}