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

#ifndef ASSIGNMENT4_PROCESS_H
#define ASSIGNMENT4_PROCESS_H

using namespace std;
// including libraries.
#include <iostream>
#include <string.h>
#include <string>
//defining array size.
#define ARRAY_SIZE 10
// declaring extern variable.
extern unsigned int Timer;


//This struct story the data for storing into history array.
struct History_Data {
	public:
		string letter;
		unsigned int value;
};


//This is datastructure of process.
class Process {

	public:
		// Constructors.
		Process();
		Process(unsigned int );
		unsigned int priority; // data variable for priority.
		string processName;
		int processID;
		unsigned int arrivalTime = 0;
		History_Data History[ARRAY_SIZE];

		unsigned int sub = 0;

		unsigned int CPUTimer = 0;
		unsigned int IOTimer = 0;

		unsigned int CPUTotal = 0;
		unsigned int ITotal = 0;
		unsigned int OTotal = 0;

		unsigned int CPUCount = 0;
		unsigned int ICount = 0;
		unsigned int OCount = 0;

		void printDetails();
};


#endif //ASSIGNMENT4_PROCESS_H
