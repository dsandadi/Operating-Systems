
/****************************************
  Assignment - 3
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 9/26/2017
TA                      : David Wiilams
Purpose                 : This program creates mini shell that executes 
			  user commands
Execution               : make
			./Assign3
 ****************************************/


#ifndef ASSIGN3_H
#define ASSIGN3_H

// including standard libraries.
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
// Creating constant pipe.
#define PIPE "||"
#define BUFFER_SIZE 1024


//defining boolean datatype.
typedef int bool;
#define true 1
#define false 0

// defining constants.
#define READ_END 0
#define WRITE_END 1
#define PIPE_SIZE 4
#define ARGS_SIZE 6
#define BUFFER_SIZE 1024

//Function prototypes.
char* removeWhiteSpaces(char*);
int parseCommand(char*,char*,char**);

#endif
