#include"mbed.h"


//initialization
AnalogOut Aout(A4);

int main()
{
    while(1){
        Aout = 0.152;
        ThisThread::sleep_for(2000ms);
        Aout = 0.303;
        ThisThread::sleep_for(2000ms);
        Aout = 0.606;
        ThisThread::sleep_for(2000ms);
        Aout = 0.758;
        ThisThread::sleep_for(2000ms);
    }
}