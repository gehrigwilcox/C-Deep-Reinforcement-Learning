/*
 * fileWriter.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */


#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "fileIO.h"


#define ALL_USER_RW S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH



int openFileForReading(char file[]){

	return open(file, O_RDONLY);

}

int openFileForWriting(char file[]){

	//Open file with writing permissions and append to the file
	//If file does not exist, create it
	//If I create a file, give all users Read/Write permissions

	return open(file, O_WRONLY | O_APPEND | O_CREAT, ALL_USER_RW);

}

int openFileForOverwriting(char file[]){

	//Open file with writing permissions and overwrite file
	//If file does not exist, create it
	//If I create a file, give all users Read/Write permissions

	return open(file, O_WRONLY | O_TRUNC | O_CREAT, ALL_USER_RW);

}

int closeFile(int file){

	//close an open file

	return close(file);

}

int writeToFile(int file, char data[]){


	return write(file, data, strlen(data)) == strlen(data) ? 0 : -1;

}

void readFromFile(int file, char data[]){

	read(file, data, strlen(data));

}
