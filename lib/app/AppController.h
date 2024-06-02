#pragma once

#include "mbed.h"
#include "SSD1306.h"

class AppController
{
    public: 
        AppController(); // Konstruktor
        void Init();
        void step();
        
        DigitalOut *led1;
        DigitalInOut *PowerLED;
        DigitalInOut *PowerButton;
        DigitalInOut *PowerRelais;
        I2C *i2c_display;
        SSD1306_I2c *oled;
        int pwr;
        int pwrCounter;
        int pwrWaitOn;
        int pwrWaitOff;

        void showErrorScreen();
        void showMainScreen();
        void showFullScreen();
        void showPwrCtrlScreen();
        void showPwrStatus();
        int getInitState();
        void showNextFull();
        void showNextAtt();
        void showNextOff();
        void pwrLEDoff();
        void pwrLEDon();
        void pwrRelaisOn();
        void pwrRelaisOff();
        void setPwrSetting(int _pwr);
        int getPwrSetting();
        void calcWaitTimes();
        void showSetupScreen();
        void showSetupMsg();
        void savePwrSetting();

    private:
        int debouncecount;
        int pwrSetting;

};