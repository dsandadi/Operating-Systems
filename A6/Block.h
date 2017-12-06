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


#ifndef A6_BLOCK_H
#define A6_BLOCK_H

#include <iostream>
#include <string>
using namespace std;
class MemoryBlock{
public:
    int start_address;
    int block_size;
    string process_ID;
    string mem_block_ID;
    MemoryBlock * blockPointer1;
    MemoryBlock * blockPointer2;
    MemoryBlock(int,int,string,string);
    MemoryBlock(int,int);
    void printBlock();
};


#endif //A6_BLOCK_H
