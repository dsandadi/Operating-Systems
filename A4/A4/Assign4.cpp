using namespace std;

#include "Assign4.h"
#include <string>
#include <cstdlib>

/*************************************
 *
 * @param p1
 * @param p2
 * @return
 */

int myComparator::operator()(const Process *p1, const Process *p2) {
    if (p1->priority == p2->priority) {
        int p1_waitingTime = Timer - (p1->arrivalTime);
        int p2_waitingTime = Timer - (p2->arrivalTime);
        return p1_waitingTime < p2_waitingTime;
    } else {
        return (p1->priority < p2->priority);
    }
}

void Process::printDetails() {
    int waiting_time = Timer - this->arrivalTime - this->CPUTotal - this->OTotal - this->ITotal;
    cout << "Cpu total active time: " << this->CPUTotal << " in " << this->CPUCount << " bursts.\n";
    cout << "Input total active time: " << this->ITotal << " in " << this->ICount << " bursts.\n";
    cout << "Output total active time: " << this->OTotal << " in " << this->OCount << " bursts.\n";
    cout << "Total Waiting Time: " << waiting_time << "\n";

}

queue<Process *> entryQueue;
priority_queue<Process *, vector<Process *>, myComparator> readyQueue;
priority_queue<Process *, vector<Process *>, myComparator> inputQueue;
priority_queue<Process *, vector<Process *>, myComparator> outputQueue;

//Process *Active = nullptr;
//Process *IActive = nullptr;
//Process *OActive = nullptr;
//int Timer = 0;


/*************************************
 *
 * @param p
 * @param pq
 */

// makes process Active (may IActive or OActive or Active).
void makeProcessActive(Process *&p, priority_queue<Process *, vector<Process *>, myComparator> &pq) {
    if (p == nullptr) {
        if (!pq.empty()) {
            p = pq.top();
            pq.pop();
        }
    }
}

/*************************************
 *
 * @param newProcess
 */

void loadQueue(Process *newProcess) {
    entryQueue.push(newProcess);
}

/*************************************
 *
 * @param newProcess
 * @param line
 */

void loadHistory(Process *newProcess, const char *line) {
    char l[100];
    strcpy(l, line);

    char *p = strtok(l, " ");

    int index = 0;
    History_Data *hist = newProcess->History;
    while (p != nullptr) {
        History_Data *h = new History_Data();
        h->letter = p;
        p = strtok(NULL, " ");
        h->value = atoi(p);
        p = strtok(NULL, " ");
        hist[index++] = *h;
    }
}

/*************************************
 *
 * @param newProcess
 * @param line
 */

void initializeProcess(Process *newProcess, const char *line) {

    char l[100];
    strcpy(l, line);
    string processName;
    processName = strtok(l, " ");
    newProcess->processName = processName;

    char *p;

    if ((p = strtok(NULL, " ")) != nullptr) {
        newProcess->priority = atoi(p);
    }

    if ((p = strtok(NULL, " ")) != nullptr) {
        newProcess->arrivalTime = atoi(p);
    }
}

/*************************************
 * ReadFile function.
 */
void readFile() {
    string line;
    ifstream inputFile("G:\\NIU_Masters\\Semester 3\\Operating Systems\\Assignments\\A4\\data4.txt");

    int count = 101;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {

            Process *p = new Process(count++);

            // initializes process member variables.
            initializeProcess(p, line.c_str());

            // check if processName is stop here then delete and break from the loop.
            if (p->processName == "STOPHERE") {
                delete (p);
                break;
            }

            loadQueue(p);
            //readyQueue.push(p);
            getline(inputFile, line);
            loadHistory(p, line.c_str());
        }
        inputFile.close();
    } else {
        cout << "unable to open file\n";
    }
}


//
/*************************************
 *
 * @param Timer
 * @return
 */

bool checkCondition(int Timer) {
    return (Timer < MAX_TIME) &&
           (!entryQueue.empty() || !readyQueue.empty() || !inputQueue.empty() || !outputQueue.empty() ||
            Active != nullptr || IActive != nullptr || OActive != nullptr);
}

/*************************************
 *
 * @param p
 * @param queueName
 */

void moveToQueue(Process *&p, string queueName, bool isIOBurstComplete) {
    if (isIOBurstComplete) {
        readyQueue.push(p);

        p = nullptr;
        return;

    }
    if (queueName == "I") {
        inputQueue.push(p);
        //readyQueue.pop();
        p = nullptr;
        //Active->CPUTimer++;
        return;
    }
    if (queueName == "O") {
        outputQueue.push(p);
        //readyQueue.pop();
        p = nullptr;
        return;
    }
}

/*************************************
 *
 * @return
 */

History_Data getProcessHistory(Process *p) {
    return p->History[p->sub];
}

void Terminate(Process *&P) {
    TerminatedProcesses++;
    cout << P->processName << " about to terminate at time " << Timer << "\n";
    P->printDetails();
    delete (P);
    P = nullptr;
}

/*************************************
 *
 * @param P
 * @param current
 * @param number_cycle_Processes
 */
void
completeBurst(Process *&P, History_Data current, unsigned int &timer, int &number_cycle_Processes,
              priority_queue<Process *, vector<Process *>, myComparator> &pq, bool isIOBurst) {
    if (P != nullptr) {
        if (timer == current.value) {

            timer = 0;
            P->sub += 1;
            //
            if (isIOBurst) {

                if (current.letter == "I")
                    P->ICount += 1;
                if (current.letter == "O")
                    P->OCount++;

                moveToQueue(P, current.letter, isIOBurst);
                //pq.pop();
                return;
            }

            current = getProcessHistory(P);

            if (current.letter == "N") {
                P->CPUCount++;
                Terminate(P);

                number_cycle_Processes--;
            } else {
                P->CPUCount++;
                moveToQueue(P, current.letter, isIOBurst);
            }
            //pq.pop();
        }
    }
}


/******************************************************
 *
 * @return
 */

void printContents() {

    cout << "Timer" << Timer << "\n";
    if (Active == nullptr)
        cout << "Active : < NULL > " << "\n";
    else
        cout << "Active :" << Active->processName << "\n";
    if (IActive == nullptr)
        cout << "IActive : < NULL > " << "\n";
    else
        cout << "IActive :" << IActive->processName << "\n";
    if (OActive == nullptr)
        cout << "OActive : < NULL > " << "\n";
    else
        cout << "OActive :" << OActive->processName << "\n";

}


void printQueue(queue<Process *> currentQueue) {
    if (currentQueue.empty()) {
        cout << "< EMPTY > ";
        return;
    }
    while (!currentQueue.empty()) {
        Process *p = currentQueue.front();
        cout << p->processName << "  ";
        currentQueue.pop();
    }
}

void printPriorityQueue(priority_queue<Process *, vector<Process *>, myComparator> pq) {
    if (pq.empty()) {
        cout << "< Empty >";
        return;
    }
    while (!pq.empty()) {
        Process *p = pq.top();
        cout << p->processName << " ";
//        cout << "Priority :" << p->priority << "\n";
//        cout << "arrivalTime :" << p->arrivalTime << "\n";
//        cout << "===========================\n";
        pq.pop();
    }

}

void printReport() {

    cout << "====================REPORT==================\n";
    printContents();

    cout << "EntryQueue contents :\n";
    printQueue(entryQueue);

    cout << "\nReadyQueue contents :\n";
    printPriorityQueue(readyQueue);

    cout << "\nInputQueue contents :\n";
    printPriorityQueue(inputQueue);

    cout << "\n outputQueue contents :\n";
    printPriorityQueue(outputQueue);
    cout << "\n";


}

int main() {

    readFile();
    // entry queue is loaded.

    // initializing variables.
    int number_cycle_Processes = 0;
    int CPU_IdleTime = 0;

    // while condition that runs until checkCondition fails.
    while (checkCondition(Timer)) {
//

//        cout << "Time Stamp :" << Timer << "\n";

        // loading readyQueue by popping a process from entry queue.
        while (number_cycle_Processes < AT_ONCE) {
            if (entryQueue.empty()) break;
            Process *processToMove = entryQueue.front();
            if ((processToMove->arrivalTime > Timer) /*|| entryQueue.empty()*/)
                break;
            entryQueue.pop();
            cout << "process " << processToMove->processName << " moved from the entry queue to ready queue at time "
                 << Timer << " \n";
            processToMove->arrivalTime = Timer;
            readyQueue.push(processToMove);
            number_cycle_Processes++;
        }

        if (Timer % 25 == 0)
            printReport();
        makeProcessActive(Active, readyQueue);

        // if no active process.
        if (Active == nullptr) {
            cout << "Incremented cpu idle time.\n";
            CPU_IdleTime++;
        }

            // If there exists an active process.
        else {
            History_Data current = getProcessHistory(Active);
//            if (Timer % 25 == 0)
//                cerr << "Active Process :" << Active->processName << "\n";


            moveToQueue(Active, current.letter, false);


            // if Active process is not moved to any input or output queue and if cpuburst is done.
            completeBurst(Active, current, Active->CPUTimer, number_cycle_Processes, readyQueue, false);
            if (Active != nullptr) {
                Active->CPUTotal++;
                Active->CPUTimer++;
            }
        }

        // Input burst starts.
        // initializes IActive process using inputQueue.


        makeProcessActive(IActive, inputQueue);

        // If there is an input active process.
        if (IActive != nullptr) {
            History_Data currentInputHistory = getProcessHistory(IActive);
//            if (Timer % 25 == 0)
//                cerr << "IActive Process :" << IActive->processName << "\n";

            completeBurst(IActive, currentInputHistory, IActive->IOTimer, number_cycle_Processes, inputQueue, true);
            if (IActive != nullptr) {
                IActive->ITotal++;
                IActive->IOTimer++;
            }

        }

        makeProcessActive(OActive, outputQueue);

        // If there is an input active process.
        if (OActive != nullptr) {
            History_Data currentInputHistory = getProcessHistory(OActive);
            completeBurst(OActive, currentInputHistory, OActive->IOTimer, number_cycle_Processes, outputQueue, true);
            if (OActive != nullptr) {
                OActive->IOTimer++;
                OActive->OTotal++;

            }
        }

        //IActive->CPUTimer++;


        Timer++;
    }


    cout << "xxxxxxxxxxxxxxxxxxxxENDxxxxxxxxxxxxxxxxxxxxxxxx\n";
    cout << "Run has ended.\n";
    cout << "amount of time CPU was idle :" << CPU_IdleTime << '\n';
    cout << "Total Terminated processes :" << TerminatedProcesses << "\n";
    cout << "Timer is " << Timer << '\n';

    printReport();
    return 0;

}