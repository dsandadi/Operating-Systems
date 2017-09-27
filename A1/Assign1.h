/****************************************
  Assignment - 1
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 9/6/2017
TA                      : David Wiilams
Purpose                 : This program creates three processes
by calling fork() system call twice.
 ****************************************/

#ifndef ASSIGN1_H
#define ASSIGN1_H

#include <iostream>
#include<string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

//defining constants that are useful in the source code.
const string processText = "My PID is ";
const string parentText = " and my parent's PID is ";
const string gChText = "I am the grand child. ";

//function prototypes.
void firstFork();
void secondFork();

#endif
