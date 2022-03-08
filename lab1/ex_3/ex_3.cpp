#include"mbed.h"

DigitalIn input(D5);
PwmOut wave(D9);

int main()
{
    if(input){
        wave.period(0.005);
        wave.write(0.5);
    }else{
        wave.period(0.002);
        wave.write(0.5);
    }
    while(1);
}