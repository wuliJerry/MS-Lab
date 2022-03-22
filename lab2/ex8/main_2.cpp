#include"mbed.h"
#include "AnalogIn.h"



//initialization
DigitalOut Red(D9);
DigitalOut Green(D10);
DigitalOut Blue(D11);
DigitalOut Yellow(D12);
AnalogIn Vin(A4);

int main()
{
    float vmea;


    //float volt = AnalogIn::read_voltage(Vin);
    while(1){
        vmea = Vin.read();
        vmea *= 3300;
        if(vmea<600){
            Red = 0;
            Green = 0;
            Blue = 0;
            Yellow = 0;
            ThisThread::sleep_for(1000ms);
        }else if(vmea<1200){
            Red = 1;
            Green = 0;
            Blue = 0;
            Yellow = 0;
            ThisThread::sleep_for(1000ms);
        }else if(vmea<1800){
            Red = 1;
            Green = 1;
            Blue = 0;
            Yellow = 0;
            ThisThread::sleep_for(1000ms);
        }else if(vmea<2400){
            Red = 1;
            Green = 1;
            Blue = 1;
            Yellow = 0;
            ThisThread::sleep_for(1000ms);
        }else{
            Red = 1;
            Green = 1;
            Blue = 1;
            Yellow = 1;
            ThisThread::sleep_for(1000ms);
        }
    }
}