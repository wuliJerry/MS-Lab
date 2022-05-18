#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mbed.h"
#include "TextLCD.h"

I2C i2c_lcd(D4, D5);
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);
DigitalIn key(D9);
DigitalIn stop(D6);// to determine whether the input of a character is finish.
DigitalOut red(D10); // start signal
DigitalOut green(D1);// get the dot
DigitalOut blue(D2);// get the touch signal
DigitalOut yellow(D3);// get the dash

#define BUF_LEN 300
#define false 0
#define true  1

/*
 *  FAKE_SPACE IS MARKING FOR A SPACE
 */
#define FAKE_SPACE '/'

/*
 * THE CHARACTER THAT BETWEEN TWO MORSE STRING
 */
#define SEPARATOR ' '

typedef int BOOL;
typedef struct Morse Morse_t;
struct Morse{
	char c[9];
};

Morse_t* new_morse() {
	Morse_t *ret;
	ret = (Morse_t*)malloc(sizeof(Morse_t));
	memset(ret->c, 0, 9);
	return ret;
}

#define NUM_LEN 10
char num[][5] = {
	{'-','-','-','-','-'},//0
	{'.','-','-','-','-'},//1
	{'.','.','-','-','-'},//2
	{'.','.','.','-','-'},//3
	{'.','.','.','.','-'},//4
	{'.','.','.','.','.'},//5
	{'-','.','.','.','.'},//6
	{'-','-','.','.','.'},//7
	{'-','-','-','.','.'},//8
	{'-','-','-','-','.'} //9
};


#define MARK_LEN 17
char mark[][8] = {
	{'.', '-', '.', '-', '.', '-', '*', '.'},//.	0
	{'-', '-', '-', '.', '.', '.', '*', ':'},//:
	{'-', '-', '.', '.', '-', '-', '*', ','},//,
	{'-', '.', '-', '.', '-', '.', '*', ';'},//;
	{'.', '.', '-', '-', '.', '.', '*', '?'},//?
	{'-', '.', '.', '.', '-', '*', '*', '='},//=
	{'.', '-', '-', '-', '-', '.', '*', '\''},//'
	{'-', '.', '.', '-', '.', '*', '*', '/'},///
	{'-', '.', '-', '.', '-', '-', '*', '!'},//!
	{'-', '.', '.', '.', '.', '-', '*', '-'},//-
	{'.', '.', '-', '-', '.', '-', '*', '_'},//_
	{'.', '-', '.', '.', '-', '.', '*', '"'},//"
	{'-', '.', '-', '-', '.', '*', '*', '('},//(
	{'-', '.', '-', '-', '.', '-', '*', ')'},//)
	{'.', '.', '.', '-', '.', '.', '-', '$'},//$
	{'.', '-', '.', '.', '.', '*', '*', '&'},//&
	{'.', '-', '-', '.', '-', '.', '*', '@'} //@	16
};

#define CHARACTER_LEN 26
char a2[][4] = {
    {'.','-','*','*'},//A
    {'-','.','.','.'},//B
    {'-','.','-','.'},//C
    {'-','.','.','*'},//D
    {'.','*','*','*'},//E
    {'.','.','-','.'},//F
    {'-','-','.','*'},//G
    {'.','.','.','.'},//H
    {'.','.','*','*'},//I
    {'.','-','-','-'},//J
    {'-','.','-','*'},//K
    {'.','-','.','.'},//L
    {'-','-','*','*'},//M
    {'-','.','*','*'},//N
    {'-','-','-','*'},//O
    {'.','-','-','.'},//P
    {'-','-','.','-'},//Q
    {'.','-','.','*'},//R
    {'.','.','.','*'},//S
    {'-','*','*','*'},//T
    {'.','.','-','*'},//U
    {'.','.','.','-'},//V
    {'.','-','-','*'},//W
    {'-','.','.','-'},//X
    {'-','.','-','-'},//Y
    {'-','-','.','.'} //Z
};

BOOL morse2num(Morse_t *morse, char *n) {
	int i = 0;

	for (; i < NUM_LEN; i++) {
		if (num[i][0] == morse->c[0] &&
			num[i][1] == morse->c[1] &&
			num[i][2] == morse->c[2] &&
			num[i][3] == morse->c[3] &&
			num[i][4] == morse->c[4] ) {

			*n = (char)(i + 48);
			return true;
		}
	}
	return false;
}
BOOL morse2mark(Morse_t *morse, char *n) {
	int a = 0;
	for (; a < MARK_LEN; a++) {
		if (mark[a][0] == morse->c[0] &&
			mark[a][1] == morse->c[1] &&
			mark[a][2] == morse->c[2] &&
			mark[a][3] == morse->c[3] &&
			mark[a][4] == morse->c[4] &&
			mark[a][5] == morse->c[5] &&
			mark[a][6] == morse->c[6] ) {

			*n = mark[a][7];
			return true;
		}
	}
	return false;
}

BOOL morse2str(Morse_t *morse, char *ch) {
	int i = 0;
	for (i = 0; i < CHARACTER_LEN; i++) {
		if (a2[i][0] == morse->c[0] &&
			a2[i][1] == morse->c[1] &&
			a2[i][2] == morse->c[2] &&
			a2[i][3] == morse->c[3]) { 

			*ch =  (char)(i + 97);
			return true;
		}
	}
	return false;
}

void morse_str_to_str(char *morse ,char *string, int buf_len) {
	Morse_t *temp = new_morse();
	int a = 0;
	int b = 0;
	int c = 0;
	int len = 0;
	char ch = '*';

	memset(temp->c, '*', 8);//fill the morse-array with '*'
	len = strlen(morse);

	for ( ; a < len; a ++) {
		if (c > buf_len) {
			printf("the string buffer is too little\n");
			return;
		}

		if (morse[a] != SEPARATOR && morse[a] != FAKE_SPACE)
			temp->c[b++] = morse[a];
		else if (morse[a] == SEPARATOR && morse[a-1] != FAKE_SPACE) {//get one charactor
			if (true == morse2str(temp, &ch) && b < 5) {
				string[c++] = ch;
			} else if (true == morse2mark(temp, &ch)) {
				string[c++] = ch;
			} else if (true == morse2num(temp, &ch)) {
				string[c++] = ch;
			} else {
				printf("has morse that not be decoded !\n");
			}

			//clean
			b = 0;
			memset(temp->c, '*' ,8);
		} else if (morse[a] == FAKE_SPACE) { //have a space
			string[c++] = ' ';
		}
	} 
}



int main()
{
	char mor[BUF_LEN];
	char str[BUF_LEN];
	
	memset(str, 0, BUF_LEN);
    memset(mor, 0, BUF_LEN);

    int i = 0;
    while(stop == 1) {
        
        red = 1;
        ThisThread::sleep_for(700ms);
		red = 0;
		ThisThread::sleep_for(300ms);
        if (key == 1) {
            blue = 1;
            ThisThread::sleep_for(300ms);
            blue = 0;
            ThisThread::sleep_for(200ms);
            if (key == 1) {
                yellow = 1;
                ThisThread::sleep_for(500ms);
                yellow = 0;
                
                mor[i] = '-';
            } else {
                green = 1;
                ThisThread::sleep_for(500ms);
                //while(key==1);
                green = 0;

                mor[i] = '.';
            }
        } else {
            red = 0;
            ThisThread::sleep_for(200ms);
            red = 1;
            ThisThread::sleep_for(200ms);
            red = 0;
            ThisThread::sleep_for(200ms);
            red = 1;
            ThisThread::sleep_for(200ms);
            red = 0;
            ThisThread::sleep_for(200ms);
            mor[i] = ' ';
            green = 1;
            blue = 1;
            yellow = 1;
            ThisThread::sleep_for(1000ms);
            green = 0;
            blue = 0;
            yellow = 0;
        }    
        lcd.putc((int)mor[i]);
        i ++;
    }

	morse_str_to_str(mor, str, BUF_LEN);

    //lcd.printf("%s", mor);
    //ThisThread::sleep_for(5s);
    lcd.cls();

    lcd.printf("%s", str);

    green = 1;
    blue = 1;
    yellow = 1;
    red = 1;

    ThisThread::sleep_for(100s);

} 