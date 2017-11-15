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

#include "Assign4.h"
#include <string>
#include <cstdlib>
#include "Process.h"

/*************************************
 *
 * Function : operator
 * Purpose :  Compares two processes waiting, to push them in to priority queue.
 * Returns : integer value representing the comparision value between two processes.
 */
unsigned int Timer = 0;
int myComparator::operator()(const Process *p1, const Process *p2) {
    if (p1->priority == p2->priority) {
        int p1_waitingTime = Timer - (p1->arrivalTime);
        int p2_waitingTime = Timer - (p2->arrivalTime);
        return p1_waitingTime < p2_waitingTime;
    } else {
        return (p1->priority < p2->priority);
    }
}

// Global queues declaration.

queue<Process *> entryQueue;
priority_queue<Process *, vector<Process *>, myComparator> readyQueue;
priority_queue<Process *, vector<Process *>, myComparator> inputQueue;
priority_queue<Process *, vector<Process *>, myComparator> outputQueue;


/*************************************
 * Function : makeProcessActive
 * Purpose : This function makes given process active, by poppin a process from priority queue.
 * Return : Returns nothing.
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
 * Function : loadHistory
 * Purpose : loads the history array with the process details.
 * Return : Nothing.
 */

void loadHistory(Process *newProcess, const char *line) {
    char l[100];// character buffer array.
    strcpy(l, line);// copying

    //tokenizing starts from here.
    char *p = strtok(l, " ");

    int index = 0;
    History_Data *hist = newProcess->History;
    // loading the history array.
    while (p != nullptr) {
        History_Data *h = new History_Data();
        h->letter = p;
        // loading p.
        p = strtok(NULL, " ");
        h->value = atoi(p);
        p = strtok(NULL, " ");
        hist[index++] = *h;

    }
}

/*************************************
 *
 * Function : initializeProcess
 * Purpose : initializes newly create processes, using line string.
 */

void initializeProcess(Process *newProcess, const char *line) {

    char l[100];
    strcpy(l, line);// copies to temporary buffer.
    string processName;
    //tokenizing start from here.
    processName = strtok(l, " ");
    newProcess->processName = processName;

    char *p;

    if ((p = strtok(NULL, " ")) != nullptr) {
        //setting new process priority.
        newProcess->priority = atoi(p);
    }

    if ((p = strtok(NULL, " ")) != nullptr) {
        newProcess->arrivalTime = atoi(p);
    }
}

/*************************************
 * Function : ReadFile
 * Purpose : Reads the input file and loads processes in to their corresponding queues.
 * Returns : Nothing.
 */
void readFile() {
    string line;// line as a string variable.
    // opening the file.
    ifstream inputFile("data4.txt");

    int count = INITIAL_PROCESS_NUMBER;
    // check if inputfile is open or not.
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            // creating a new process.
            Process *p = new Process(count++);

            // initializes process member variables.
            initializeProcess(p, line.c_str());

            // check if processName is stop here then delete and break from the loop.
            if (p->processName == "STOPHERE") {
                delete (p);// deleting the process.
                p = nullptr;// setting p to nullptr.
                break;
            }

            entryQueue.push(p);// loading entryqueue.
            // loadEntryQueue(p);
            //readyQueue.push(p);
            getline(inputFile, line);// gets line from input file.
            loadHistory(p, line.c_str());// loads history.
        }
        inputFile.close();// closes inputFile.
    } else {
        cout << "unable to open file\n";
    }
}


//
/*************************************
 *
 * Function : checkCondition.
 * Purpose : checks the given condition and returns corresponding value.
 */

bool checkCondition(int Timer) {
    return (Timer < MAX_TIME) &&
           (!entryQueue.empty() || !readyQueue.empty() || !inputQueue.empty() || !outputQueue.empty() ||
            Active != nullptr || IActive != nullptr || OActive != nullptr);
}

/*************************************
 *
 * Function : moveToQueue
 * Purpose : moves the given process to corresponding queue by checking for IO operation.
 */

void moveToQueue(Process *&p, string queueName, bool isIOBurstComplete) {
    if (isIOBurstComplete) {
        readyQueue.push(p);// push to ready queue incase of IOBurst.
        p = nullptr;
        return;
    }

    if (queueName == "I") {
        inputQueue.push(p);// pushing to inputQueue.
        //readyQueue.pop();
        p = nullptr;
        //Active->CPUTimer++;
        return;
    }
    //pushing to output queue.
    if (queueName == "O") {
        outputQueue.push(p);
        //readyQueue.pop();
        p = nullptr;
        return;
    }
}

/*************************************
 *
 * Function : getProcessHistory.
 * Purpose : to retrieve process history.
 * Returns : History_Data value.
 */

History_Data getProcessHistory(Process *p) {
    return p->History[p->sub];
}

/*************************************
 *
 * Function : Terminate.
 * Purpose : terminates the given process.
 * Returns : Nothing..
 */

void Terminate(Process *&P) {
    TerminatedProcesses++; //increment terminated process.
    cout << "\nProcess " << P->processName << " terminated at time " << Timer << "\n";
    P->printDetails();
    delete (P);// deletes the process.
    P = nullptr;// set p to null pointer.
}

/*************************************
 *
 * Function : completeBurst.
 * Purpose : completes the burst operations.
 * Returns : Nothing.
 */

void completeBurst(Process *&P, History_Data current, unsigned int &timer, int &number_cycle_Processes,
                   priority_queue<Process *, vector<Process *>, myComparator> &pq, bool isIOBurst) {
    //if p is null pointer do nothing.
    if (P != nullptr) {
        // if timer reaches the given burst time go to next burst.
        if (timer == current.value) {

            timer = 0;// set timer back to zero.
            P->sub += 1;// go to next burst.
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
            // else get process history.
            current = getProcessHistory(P);
            // if current letter is N then terminate.
            if (current.letter == "N") {
                P->CPUCount++;
                Terminate(P);

                number_cycle_Processes--;// decrement processes in cycle.
            } else {
                P->CPUCount++;
                moveToQueue(P, current.letter, isIOBurst);// move to corresponding queue.
            }
        }
    }
}


/******************************************************
 *
 * Function : printContents.
 * Purpose : prints the contents such as details about the processes.
 * Returns : Nothing.
 */

void printContents() {

    cout << "\nStatus at time " << Timer << "\n";
    // if active is nullptr.
    if (Active == nullptr)
        cout << "No current Active process, CPU idle." << "\n";
    else
        cout << "Active :" << Active->processName << "\n";
    // printing IActive process.
    if (IActive == nullptr)
        cout << "No current IActive process, Input idle." << "\n";
    else
        cout << "IActive :" << IActive->processName << "\n";
    // printing OActive process.
    if (OActive == nullptr)
        cout << "NO current OActive process, Output idle." << "\n";
    else
        cout << "OActive :" << OActive->processName << "\n";
}

/******************************************************
 *
 * Function : printQueue.
 * Purpose : prints the contents of queue.
 * Returns : Nothing.
 * Arguments currentQueue.
 */
void printQueue(queue<Process *> currentQueue) {
    // if currentQueue is empty.
    if (currentQueue.empty()) {
        cout << "< EMPTY > ";
        return;
    }
    //printing the queue, if not empty.
    while (!currentQueue.empty()) {
        Process *p = currentQueue.front();
        cout << p->processName << "  ";
        currentQueue.pop();// popping elements from queue.
    }
}

/******************************************************
 *
 * Function : printPriorityQueue.
 * Purpose : prints the contents of  priority queue.
 * Returns : Nothing.
 */

void printPriorityQueue(priority_queue<Process *, vector<Process *>, myComparator> pq) {
    // if priority queue is empty print empty.
    if (pq.empty()) {
        cout << "< Empty >";
        return;
    }
    // if priority queue is not empty, then print the contents of queue.
    while (!pq.empty()) {
        Process *p = pq.top();
        cout << p->processName << " ";
        pq.pop();// pop process.
    }
}

/******************************************************
 *
 * Function : printReport.
 * Purpose : prints report.
 * Returns : Nothing.
 */

void printReport() {

    printContents();// calls printContents.

    cout << "\nContents of Entry queue:\n";
    printQueue(entryQueue);// prints entryQueue.

    cout << "\nContents of ReadyQueue:\n";
    printPriorityQueue(readyQueue);// prints readyQueue.

    cout << "\nContents of InputQueue:\n";
    printPriorityQueue(inputQueue);// prints inputQueue.

    cout << "\nContents of OutputQueue:\n";
    printPriorityQueue(outputQueue);// prints outputQueue.
    cout << "\n";

}

/******************************************************
 *
 * Function : main.
 * Purpose : entry point of the program.
 * Returns : integer value representing status of exit.
 */

int main() {

    readFile();// reads the file.
    // entry queue is loaded.

    // initializing variables.
    int number_cycle_Processes = 0;
    int CPU_IdleTime = 0;

    // while condition that runs until checkCondition fails.
    while (checkCondition(Timer)) {

        // loading readyQueue by popping a process from entry queue. This will load the ready Queue.
        while (number_cycle_Processes < AT_ONCE) {
            if (entryQueue.empty()) break;
            // taking top process of entry queue.
            Process *processToMove = entryQueue.front();
            // checking condition.
            if ((processToMove->arrivalTime > Timer) /*|| entryQueue.empty()*/)
                break;
            // popping a process out of entryQueue.
            entryQueue.pop();
            cout << "\nProcess " << processToMove->processName << " moved from the entry queue to ready queue at time "
                 << Timer << " \n";
            //setting the arrival time of newly entering process
            processToMove->arrivalTime = Timer;
            // pushing the new process in to ready queue.
            readyQueue.push(processToMove);
            number_cycle_Processes++;//incrementing number of processes in cycle.
        }
        //printing the report at every multiples of HOW_OFTEN.
        if (Timer % HOW_OFTEN == 0)
            printReport();

        // making processActive by picking from readyQueue.
        makeProcessActive(Active, readyQueue);

        // if there is still no active process. Incrementing the CPU_idleTime.
        if (Active == nullptr) {
            CPU_IdleTime++;
        }
            // If there exists an active process.
        else {
            History_Data current = getProcessHistory(Active); // gathering the history.

            moveToQueue(Active, current.letter, false);// moving to proper queue.


            // if Active process is not moved to any input or output queue and if cpuburst is done.
            completeBurst(Active, current, Active->CPUTimer, number_cycle_Processes, readyQueue, false);
            // if Active still exists increment the CPUTimer and CPUTotal.
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
            History_Data currentInputHistory = getProcessHistory(IActive);// gathering history of IActive process.
            // completing the input burst
            completeBurst(IActive, currentInputHistory, IActive->IOTimer, number_cycle_Processes, inputQueue, true);
            // if IActive still exists.
            if (IActive != nullptr) {
                IActive->ITotal++;
                IActive->IOTimer++;
            }
        }
        // output burst starts here.
        // Activating OActive process from outputQueue.
        makeProcessActive(OActive, outputQueue);

        // If there is an output active process.
        if (OActive != nullptr) {
            History_Data currentInputHistory = getProcessHistory(OActive);// gathering data.
            // completing burst.
            completeBurst(OActive, currentInputHistory, OActive->IOTimer, number_cycle_Processes, outputQueue, true);
            // if OActive still exists.
            if (OActive != nullptr) {
                OActive->IOTimer++;
                OActive->OTotal++;
            }
        }
        Timer++;// incrementing the timer.
    }
    // printitng the summary.
    cout << "\nThe Run has ended.\n";
    cout << "The final value of timer is " << Timer << '\n';
    cout << "amount of time CPU was idle :" << CPU_IdleTime << '\n';
    cout << "Total Number of Terminated processes :" << TerminatedProcesses << "\n";
    //Finally printing the report after the run is ended.
    printReport();
    return 0;
}
