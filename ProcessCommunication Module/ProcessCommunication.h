
/****************************************
  Assignment - 2
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 9/14/2017
TA                      : David Wiilams
Purpose                 : This program creates three processes
by using fork() and three pipes using pipe() system call, which
facilitates those processes to communicate.
Execution               : make
                         ./Assign2
 ****************************************/


#ifndef ASSIGN2_H
#define ASSIGN2_H
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// defining constants.
#define WRITE_END 1
#define READ_END 0
#define SIZE 10
#define RANGE 99999999

//Function prototypes.
void pWork(int*, int*);
void cWork(int*, int*);
void gWork(int*, int*);
void processData(char*, char*);

void commonWork(int*, int*, char*);


#endif
