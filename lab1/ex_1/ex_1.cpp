/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

//initialize the output pin
DigitalOut red(D5);
DigitalOut green(D6);

int main()
{
    while(1){
        //stage 1
	    red = 1;
	    green = 0;
        ThisThread::sleep_for(1000ms);
        //stage 2
        red = 0;
        green = 1;
        ThisThread::sleep_for(1000ms); 
    }
    
}
