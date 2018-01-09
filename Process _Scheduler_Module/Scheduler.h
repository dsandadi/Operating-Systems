/****************************************
  Assignment - 4
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 10/13/2017
TA                      : David Wiilams
Purpose                 : This program does priority process scheduling simulation.
Execution               : make
./Assign4
 ****************************************/

#ifndef ASSIGNMENT4_ASSIGN4_H
#define ASSIGNMENT4_ASSIGN4_H

using namespace std;

//declaring constants.
// length of run of program.
#define MAX_TIME 500
// degree of multiprogramming.
#define AT_ONCE 5
#define QUEUE_SIZE 20
#define HOW_OFTEN 25
#define INITIAL_PROCESS_NUMBER 101

// including libraries.
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "Process.h"

#include<queue>

// myComparator class.

class myComparator {
	public:
		int operator()(const Process *, const Process *);

};

//Funcction prototypes.
bool checkCondition(int);

void moveToQueue(Process *);

History_Data getProcessHistory(Process *);
//void makeProcessActive(Process*, priority_queue);



//Global variables.

Process *Active = nullptr;
Process *IActive = nullptr;
Process *OActive = nullptr;
int TerminatedProcesses = 0;


#endif //ASSIGNMENT4_ASSIGN4_H
