//
// Created by DINESH on 10/4/2017.
//

#ifndef ASSIGNMENT4_ASSIGN4_H
#define ASSIGNMENT4_ASSIGN4_H

//declaring constants.
// length of run of program.
#define MAX_TIME 500
// degree of multiprogramming.
#define AT_ONCE 5
#define QUEUE_SIZE 20
#define ARRAY_SIZE 10
#define HOW_OFTEN 25

// including libraries.
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include<queue>

//This struct story the data for storing into history array.
struct History_Data {
public:
    string letter;
    int value;
};



// myComparator class.

//This is datastructure of process.
class Process {

public:
    Process() {

    }

    Process(unsigned int ID) {
        processID = ID;
    }

    unsigned int priority;
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


//queue<Process *> entryQueue;
//priority_queue<Process *, vector<Process *>, myComparator> readyQueue;
//priority_queue<Process *, vector<Process *>, myComparator> inputQueue;
//priority_queue<Process *, vector<Process *>, myComparator> outputQueue;
Process *Active = nullptr;
Process *IActive = nullptr;
Process *OActive = nullptr;
int Timer = 0;
int TerminatedProcesses = 0;


#endif //ASSIGNMENT4_ASSIGN4_H
