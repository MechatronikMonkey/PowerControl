/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "AppController.h"
#include "mbed.h"

int main()
{
    AppController MyApp;

    // Get inital time to calculate time slots for sm call
    auto wake_time = Kernel::Clock::now() + 100ms;

    // Do Inits routines for the app
    MyApp.Init();

    while (true)
    {
        // Call the AppController step to start state machine.
        MyApp.step();

        // Sleep rest of the time slot
        ThisThread::sleep_until(wake_time);

        // Calculate next time slot
        wake_time += 100ms;
    }
}
