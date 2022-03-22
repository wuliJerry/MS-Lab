#include"mbed.h"

/****
D10 - A
D9 - B
Vcc X - 3v3
GND ENABLE - gnd
output-pin - x0 x1 x2 x3
x0 - green
x1 - red
x2 - white
x3 - yellow
****/

/****
Meanwhile, the Truth Table are as follows
A-L B-L x0
A-H B-L x1
A-L B-H x2
A-H B-H x3
 ****/


//initialization
DigitalOut multiA(D10);
DigitalOut multiB(D9);

int main()
{
    //make the judgement
    while(1){
        for(int i = 0 ;i<4 ;i++){
            switch(i%4){
                case 0://Green
                    multiA = 0;
                    multiB = 0;
                    ThisThread::sleep_for(200ms);
                    break;
                case 1://Red
                    multiA = 1;
                    multiB = 0;
                    ThisThread::sleep_for(200ms);
                    break;
                case 2://Blue
                    multiA = 0;
                    multiB = 1;
                    ThisThread::sleep_for(200ms);
                    break;
                case 3://Yellow
                    multiA = 1;
                    multiB = 1;
                    ThisThread::sleep_for(200ms);
                    break;
            }
        }
    }
}