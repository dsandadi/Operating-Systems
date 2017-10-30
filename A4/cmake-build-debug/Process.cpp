//
// Created by DINESH on 10/12/2017.
//
#include "Process.h"

/*************************************
 * Function : PrintDetails.
 * Purpose : PrintDetails of the process.
 * Returns : Nothing.
 */
void Process::printDetails() {
    // calculates the waiting time of the process.
    int waiting_time = Timer - this->arrivalTime - this->CPUTotal - this->OTotal - this->ITotal;

    cout << "\nName: " << this->processName;
    cout << "\nStart time: " << this->arrivalTime << " End time: " << Timer;
    cout << "\nTotal CPU time = " << this->CPUTotal << " in " << this->CPUCount << "CPU bursts.";
    cout << "\nTotal Input time = " << this->ITotal << " in " << this->ICount << "Input bursts.";
    cout << "\nTotal Output time = " << this->OTotal << " in " << this->OCount << "Output bursts.";
    cout << "\nTotal Waiting Time = " << waiting_time << "\n";

}

Process::Process() {
}

Process::Process(unsigned int ID) {
    processID = ID;
}