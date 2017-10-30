//
// Created by DINESH on 10/12/2017.
//

#ifndef ASSIGNMENT4_PROCESS_H
#define ASSIGNMENT4_PROCESS_H

#define ARRAY_SIZE 10

//This struct story the data for storing into history array.
struct History_Data {
public:
    string letter;
    int value;
};


//This is datastructure of process.
class Process {

public:
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


#endif //ASSIGNMENT4_PROCESS_H
