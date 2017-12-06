/****************************************
           Assignment - 6
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 11/15/2017
TA                      : David Wiilams
Purpose                 : Simulation program for memory management using various
algorithms like first-fit and best-fit.
Execution               : make
./Assign6
 ****************************************/


#ifndef A6_ASSIGN6_H
#define A6_ASSIGN6_H
#define HOW_OFTEN 5
#define KB 1024
#define MB 1048576
//#define EXIT_FAILURE 20
#include "Block.h"
#include <iostream>
#include <list>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "Block.h"
#include <limits>


//Function prototypes.
void printList(list<MemoryBlock*> );
void initialize();
void attachProcessToAvail(MemoryBlock*);
void normalizeTheAvailList();
MemoryBlock* findTheProcess(string ,string );
//void loadProcess(string,int, string,string);
void deallocateProcess(string,string,string);
void terminateProcess(string);
list<MemoryBlock*> ::iterator findFirstFitBlock(int );
list<MemoryBlock*> ::iterator findBestFitBlock(int );
void allocateProcess(list<MemoryBlock* >::iterator, string, int, string);
//void processFirstFit(string, int , string , string );
void loadProcess(string, int, string, string);
#endif //A6_ASSIGN6_H
