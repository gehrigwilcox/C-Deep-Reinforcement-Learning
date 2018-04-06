/*
 * prettyPrint.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */

#include<stdio.h>

#include "prettyPrint.h"

/*

    ANSI Escape Sequences

    \x1B[<Line>;<Column>H sets the cursor position


    \x1B[<Value>A moves the cursor up value amount
    \x1B[<Value>B moves the cursor down value amount
    \x1B[<Value>C moves the cursor forward value amount
    \x1B[<Value>D moves the cursor backward value amount


    \x1B[s Saves the cursor position
    \x1B[u Restores the cursor position

    \x1B[2J Clears the screen

    \x1B[K Clears current Line

    \x1B[<Value>;...;<Value>m sets graphics mode

        Values:
            0: all attributes off
            1: Bold on
            4: Underscore
            5: Blink on
            7: Reverse Video on
            8: Concealed on

            30: Black foreground
            31: Red foreground
            32: Green foreground
            33: Yellow foreground
            34: Blue foreground
            35: Magenta foreground
            36: Cyan foreground
            37: White foreground

            40: Black background
            41: Red background
            42: Green background
            43: Yellow background
            44: Blue background
            45: Magenta background
            46: Cyan background
            47: White background

*/


#define ESCAPE_CODE "\x1B["



void clearScreen(){

	printf(ESCAPE_CODE "2J");

	setCursorPos(1,1);

}

void setTextColor(enum color text){

	printf(ESCAPE_CODE "%uJ", text+30);

}

void setBackgroundColor(enum color background){

	printf(ESCAPE_CODE "%uJ", background+40);

}

void clearFormatting(){

	printf(ESCAPE_CODE "0J");

}

void setFormatting(enum format text){

	switch(text){

		case BOLD:

			printf(ESCAPE_CODE "1J");

			break;

		case UNDERSCORE:

			printf(ESCAPE_CODE "4J");

			break;

		case BLINK:

			printf(ESCAPE_CODE "5J");

			break;

		default:
			printf("");
	}

}

void setCursorPos(int x, int y){

	printf(ESCAPE_CODE "%u;%uH", x, y);

}
