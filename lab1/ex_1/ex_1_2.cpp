/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut red(D5);
DigitalOut green(D6);
DigitalOut pin_1(D9);


int main()
{   
    pin_1 = 1;
    while(1){
	    red = 1;
	    green = 0;
        ThisThread::sleep_for(1000ms);
        red = 0;
        green = 1;
        ThisThread::sleep_for(1000ms); 
    }
    
}
