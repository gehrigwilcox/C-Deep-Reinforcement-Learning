/*
 * fileWriter.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */

#ifndef TOOLS_FILEIO_H_
#define TOOLS_FILEIO_H_


int openFileForReading(char file[]);

int openFileForWriting(char file[]);

int openFileForOverwriting(char file[]);

int closeFile(int file);

int writeToFile(int file, char data[]);

void readFromFile(int file, char data[]);

#endif /* TOOLS_FILEIO_H_ */
