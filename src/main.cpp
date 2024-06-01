/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "SSD1306.h"

#define WAIT_TIME_MS 100 
DigitalOut led1(LED1);
DigitalInOut PowerLED(PA_11, PIN_OUTPUT, OpenDrainNoPull, 1);
DigitalInOut PowerButton(PB_5, PIN_INPUT, PullUp, 0);
DigitalInOut PowerRelais(PB_4, PIN_OUTPUT, OpenDrainNoPull, 1);

// an I2C sub-class that provides a constructed default
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};

I2CPreInit gI2C(PB_7,PB_6); // SDA, SCL
SSD1306_I2c gOled(gI2C,PA_8,0x7A,64,128); // Reset PIN

int main()
{

    while (true)
    {
        led1 = !led1;

        if (PowerButton.read() == 0)
        {
            PowerLED = 0;
            PowerRelais = 0;
        }
        else
        {
            PowerLED = 1;
            PowerRelais = 1;
        }
        
        gOled.clearDisplay();
        gOled.setTextCursor(5,5);
        gOled.printf("Hallo Welt!");
        gOled.display();
        thread_sleep_for(WAIT_TIME_MS);
    }
}
