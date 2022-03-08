/* mbed Microcontroller Library
 * Copyright (c) 2022 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

//initialize the output pin
DigitalOut red(D5);
DigitalOut green(D6);
DigitalOut pin_0(D9);


int main()
{   
    //initialize the pin_0's voltage
    pin_0 = 0;
    while(1){
        //stage 1
	    red = 1;
	    green = 0;
        //stage 2
        ThisThread::sleep_for(1000ms);
        red = 0;
        green = 1;
        ThisThread::sleep_for(1000ms); 
    }
    
}
