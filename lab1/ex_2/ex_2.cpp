/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

//initialization
PwmOut wave(D9);


int main()
{   
    //generalize the square wave
    wave.period(0.001);
    wave.write(0.5);
    while(1);
}
