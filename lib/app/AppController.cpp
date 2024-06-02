#include "AppController.h"
#include "mbed.h"
#include "SSD1306.h"
#include "PowerControl_SM.h"

///////////////////////////////////////////// CONSTANTS /////////////////////////////////////////////




///////////////////////////////////////////// PROTOTYPES /////////////////////////////////////////////




///////////////////////////////////////////// LOCAL VARS /////////////////////////////////////////////

static PowerControl_SM MyPwrCotrlSm;


///////////////////////////////////////////// FUNCTIONS /////////////////////////////////////////////
AppController::AppController()
{
    // THIS IS APPLICATION SETTINGS FOR THE SPECIFIC BOARD - change this if Board changes

    // Setup all Digital I/Os
    led1 = new DigitalOut(LED1);
    PowerLED = new DigitalInOut(PA_11, PIN_OUTPUT, OpenDrainNoPull, 1);
    PowerButton = new DigitalInOut(PB_5, PIN_INPUT, PullUp, 0);
    PowerRelais = new DigitalInOut(PB_4, PIN_OUTPUT, OpenDrainNoPull, 1);

    // Setup the Display Pins
    i2c_display = new I2C(PB_7,PB_6); // Set SDA, SCL Pins

    // Setup the OLED Driver
    oled = new SSD1306_I2c(*i2c_display,PA_8,0x7A,64,128); // PA_8 = Reset PIN)

}
void AppController::Init()
{
    // Start I2C
    i2c_display->frequency(400000);
    i2c_display->start();

    debouncecount = 0;
    pwr = 0;
    pwrCounter = 0;
    pwrSetting = 30;

    // Start State machine
    PowerControl_SM_ctor(&MyPwrCotrlSm);
    PowerControl_SM_start(&MyPwrCotrlSm);

    // Link this object to upper levels.
    MyPwrCotrlSm.vars.parent = this;

}

void AppController::step()
{
    PowerControl_SM_dispatch_event(&MyPwrCotrlSm, PowerControl_SM_EventId_DO);

    //Show user that we are running
    *led1 = ! *led1;

    //////////// Handle Button press and create events ////////////

    // Check if released with a sufficent debounce time, than create event for short press
    if (*PowerButton == 1 && debouncecount > 1 && debouncecount <= 10)
    {
        //Short Button Press after waiting at least 2 cycles for debouncing
        PowerControl_SM_dispatch_event(&MyPwrCotrlSm, PowerControl_SM_EventId_SHORT_PRESS);
        debouncecount = 0;
    }
    else if (*PowerButton == 0 && debouncecount > 10)
    {
        //Long Button Press
        PowerControl_SM_dispatch_event(&MyPwrCotrlSm, PowerControl_SM_EventId_LONG_PRESS);
        debouncecount = 0;

        // Block any input for 500 ms
        ThisThread::sleep_for(500ms);
    }

    // Just count a debounce counter while button is pressed
    if (*PowerButton == 0) // Button pressed
    {
        debouncecount++;
    }
    else
    {
        debouncecount=0;
    }

}

void AppController::showErrorScreen()
{
    oled->clearDisplay();
    oled->setTextCursor(5,5);
    oled->printf("ERROR!");
    oled->display();
}

void AppController::showMainScreen()
{
    oled->clearDisplay();
    oled->setTextCursor(5,5);
    oled->printf("Pwr Cntrlr ready.");
    oled->display();
}

void AppController::showFullScreen()
{
    oled->clearDisplay();
    oled->setTextCursor(5,5);
    oled->printf("HEATING FULL");
    oled->display();
}

void AppController::showPwrCtrlScreen()
{
    oled->clearDisplay();
    oled->setTextCursor(5,5);
    oled->printf("HEATING contrld");
    oled->display();
}

void AppController::showPwrStatus()
{
    oled->setTextCursor(15,25);
    oled->printf("Power: %i %   ", pwr);
    oled->display();
}

int AppController::getInitState()
{
    // for the moment, just return 1 for a success
    return 1;
}

void AppController::showNextFull()
{
    oled->setTextCursor(5,45);
    oled->printf("press to start...  ");
    oled->setTextCursor(5,55);
    oled->printf("long press to set...");
    oled->display();
}

void AppController::showNextAtt()
{
    oled->setTextCursor(5,45);
    oled->printf("press to ctrl...  ");
    oled->setTextCursor(5,55);
    oled->printf("                    ");
    oled->display();
}  

void AppController::showNextOff()
{
    oled->setTextCursor(5,45);
    oled->printf("press to sw off...");
    oled->setTextCursor(5,55);
    oled->printf("                  ");
    oled->display();
}  
void AppController::pwrLEDoff()
{
    *PowerLED = 1;
}

void AppController::pwrLEDon()
{
    *PowerLED = 0;
}

void AppController::pwrRelaisOn()
{
    *PowerRelais = 0;
}

void AppController::pwrRelaisOff()
{
    *PowerRelais = 1;
}

int AppController::getPwrSetting()
{
    return pwrSetting;
}

void AppController::setPwrSetting(int _pwr)
{
    pwrSetting = _pwr;
}

void AppController::calcWaitTimes()
{
    pwrWaitOn = pwrSetting / 10;
    pwrWaitOff = (100 - pwrSetting) / 10;
}

void AppController::showSetupScreen()
{
    oled->clearDisplay();
    oled->setTextCursor(5,5);
    oled->printf("Set Power:");
    oled->display();
}

void AppController::showSetupMsg()
{
    oled->setTextCursor(5,45);
    oled->printf("short press to set");
    oled->setTextCursor(5,55);
    oled->printf("long press to save");
    oled->display();
}

void AppController::savePwrSetting()
{
    if (pwr > 90)
    {
        pwr = 10;
    }

    pwrSetting = pwr;
}