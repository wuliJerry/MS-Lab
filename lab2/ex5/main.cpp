#include"mbed.h"

/****
  2 3 4 5 6 9 0 1
  A B C D E F G DP
  7 6 4 2 1 9 0 5 
0 1 1 1 1 1 1 0 0   0xfc   
1 0 1 1 0 0 0 0 0   0x60  
2 1 1 0 1 1 0 1 0   0xda
3 1 1 1 1 0 0 1 0   0xf2 
4 0 1 1 0 0 1 1 0   0x66
5 1 0 1 1 0 1 1 0   0xb6
6 1 0 1 1 1 1 1 0   0xbe
7 1 1 1 0 0 0 0 0   0xe0 
8 1 1 1 1 1 1 1 0   0xfe
9 1 1 1 1 0 1 1 0   0xf6
H 0 1 1 0 1 1 1 0   0x6e
E 1 0 0 1 1 1 1 0   0x9e
L 0 0 0 1 1 1 0 0   0x1c
P 1 1 0 0 1 1 1 0   0xce
 ****/


//initialization
BusOut digiboard(D11,D10,D9,D6,D5,D4,D3,D2);

int main()
{
    while(1){
        for(int i = 0;i < 11;i++){
            switch(i){
                case 0:
                    digiboard = 0xfc;
                    ThisThread::sleep_for(500ms);
                    break;
                case 1:
                    digiboard = 0x60;
                    ThisThread::sleep_for(500ms);
                    break;
                case 2:
                    digiboard = 0xda;
                    ThisThread::sleep_for(500ms);                    
                    break;                
                case 3:
                    digiboard = 0xf2;
                    ThisThread::sleep_for(500ms);
                    break;
                case 4:
                    digiboard = 0x66;
                    ThisThread::sleep_for(500ms);
                    break;
                case 5:
                    digiboard = 0xb6;
                    ThisThread::sleep_for(500ms);
                    break;
                case 6:
                    digiboard = 0xbe;
                    ThisThread::sleep_for(500ms);
                    break;
                case 7:
                    digiboard = 0xe0;
                    ThisThread::sleep_for(500ms);
                    break;
                case 8:
                    digiboard = 0xfe;
                    ThisThread::sleep_for(500ms);
                    break;
                case 9:
                    digiboard = 0xf6;
                    ThisThread::sleep_for(500ms);
                    break;
                default:
                    digiboard = 0x6e;
                    ThisThread::sleep_for(200ms);
                    digiboard = 0x9e;
                    ThisThread::sleep_for(200ms);
                    digiboard = 0x1c;
                    ThisThread::sleep_for(200ms);
                    digiboard = 0xce;
                    ThisThread::sleep_for(200ms);                    
                    break;
            }
        }
    }
}