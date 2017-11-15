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
	cout << "\nPriority: "<< this->priority;
	cout << "\nStart time: " << this->arrivalTime << " End time: " << Timer;
	cout << "\nTotal CPU time = " << this->CPUTotal << " in " << this->CPUCount << " CPU bursts.";
	cout << "\nTotal Input time = " << this->ITotal << " in " << this->ICount << " Input bursts.";
	cout << "\nTotal Output time = " << this->OTotal << " in " << this->OCount << " Output bursts.";
	cout << "\nTotal Waiting Time = " << waiting_time << "\n";

}
// Process no argument constructor.
Process::Process() {
}
// Process single argument constructor.
Process::Process(unsigned int ID) {
	// initializing the processID of process.
	processID = ID;
}
