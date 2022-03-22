#include"mbed.h"


//initialization
AnalogOut Aout(A4);

int main()
{
    while(1){
        for(int i = 0;i < 909 ;i+=3){
            Aout = 0.001 * i;
            wait_ns(17300);
        }
    }
}