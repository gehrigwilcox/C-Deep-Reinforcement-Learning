/*
 * prettyPrint.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */

#ifndef PRETTYPRINT_H_
#define PRETTYPRINT_H_


enum color{BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

enum format{BOLD, UNDERSCORE, BLINK};


void clearScreen();

void setTextColor(enum color text);

void setBackgroundColor(enum color background);

void clearFormatting();

void setFormatting(enum format text);

void setCursorPos(int x, int y);

void clearLine();

#endif /* PRETTYPRINT_H_ */
