/****************************************
  Assignment - 2
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 9/14/2017
TA                      : David Wiilams
Purpose                 : This program creates three processes
by using fork() and three pipes using pipe() system call, which
facilitates those processes to communicate.
Execution               : make
./Assign2
 ****************************************/
#include "Assign2.h"
/**************************************************
Function : processData
Purpose : converts the input data to output data by doing
some operations on input.
Arguments : input string and output string.
Returns nothing.

 ***************************************************/
void processData(char* input, char* output) {


	int val = atoi(input);// converts string to integer.
	val = 4 * val + 3;// calculates the new value.
	sprintf(output, "%d", val);// output the new value in to a string.
}
/**************************************************
Function : cWork
Purpose :  Does the child work. 
Arguments : read end of pipe and write end of pipe.
Returns nothing.

 ***************************************************/

void cWork(int* inPipe, int* outPipe) {
	char desc[10] = "Child: ";

	commonWork(inPipe, outPipe, desc);
}
/**************************************************
Function : gWork
Purpose :  Does grand child work.
Arguments : read end of pipe and write end of pipe.
Returns nothing.

 ***************************************************/

void gWork(int* inPipe, int* outPipe) {
	char desc[20] = "Grandchild: ";

	commonWork(inPipe, outPipe, desc);
}
/**************************************************
Function : commonWork
Purpose :  Does common work.
Arguments : read end of pipe and write end of pipe,
description about the process calling it.
Returns nothing.
 ***************************************************/
void commonWork(int* inPipe, int* outPipe, char* desc) {
	char buffer[SIZE];//buffer to store processed data 
	char value[SIZE] = "1";//buffer to store input data.
	int M = 1;
	// This while loope keeps circulating the data until the range is reached.
	while (M < RANGE) {
		int index = 0;
		int size = read(inPipe[READ_END], (value + index), 1);
		// Reading from the in pipe and storing in the local buffer.
		while (value[index] != '\0' && size > 0) {
			index++;
			size = read(inPipe[READ_END], (value + index), 1);
		}
		// calls process data.
		processData(value, buffer);

		fprintf(stderr, "%-20s Value = %-8s\n", desc, buffer);
		write(outPipe[WRITE_END], buffer, strlen(buffer) + 1);
		M = atoi(buffer);// converts string to integer.
	}
}
/**************************************************
Function : pWork
Purpose :  Does parent work, which is initializing 
the circulation by writing the value in to pipeA
Arguments : read end of pipe and write end of pipe.
Returns nothing.

 ***************************************************/
void pWork(int* inPipe, int* outPipe) {

	char buffer[10] = "1";
	char desc[10]="Parent: ";
	fprintf(stderr, "%-20s Value = %-8s\n", desc, buffer); 
	// initializes circulation by writing in to pipeA.
	write(outPipe[WRITE_END], buffer, 2);
	commonWork(inPipe, outPipe, desc);// calls commonWork function.
}
/**************************************************
Function : main()
Purpose :  Entry point of the program.
Arguments : None
Returns int representing the state of exit.
 **************************************************/
int main() {

	//declaring three pipe variables.
	int pipeA[2];
	int pipeB[2];
	int pipeC[2];
	// creating pipes A, B and C.  
	if (pipe(pipeA) < 0) {
		perror("Failed to create pipeA");
		exit(-1);
	}
	if (pipe(pipeB) < 0) {
		perror("Failed to create pipeB");
		exit(-1);
	}
	if (pipe(pipeC) < 0) {
		perror("Failed to create pipeC");
		exit(-1);
	}
	// process id declaration.
	pid_t cpid;
	pid_t gpid;
	// creating the child process.
	if ((cpid = fork()) < 0) {
		perror("Failed to fork child\n");
		exit(-5);
	}

	/* Child process*/
	if (cpid == 0) {
		//creating the grand child process.
		if ((gpid = fork()) < 0) {
			perror("Failed to fork grand child\n");
			exit(-5);
		}
		// Grand child process.
		if (gpid == 0) {
			//closing unused ends of the pipe.
			close(pipeB[WRITE_END]);
			close(pipeC[READ_END]);
			//closing the pipeA completely since grand parent doesn't need it.
			close(pipeA[READ_END]);
			close(pipeA[WRITE_END]);

			gWork(pipeB, pipeC);

			//closing the other two ends.
			close(pipeC[WRITE_END]);
			close(pipeB[READ_END]);
		}//Child process.
		else {
			//closing unused ends of the pipe.
			close(pipeA[WRITE_END]);
			close(pipeB[READ_END]);
			//closing the pipeC completely since child doesn't need it.
			close(pipeC[READ_END]);
			close(pipeC[WRITE_END]);

			cWork(pipeA, pipeB);
			//closing other two ends.
			close(pipeB[WRITE_END]);
			close(pipeA[READ_END]);
			// waiting for child to terminate.
			wait(NULL);
			exit(0);
		}
	}// Parent process.
	else {

		//closing unused pipe ends.
		close(pipeA[READ_END]);
		close(pipeC[WRITE_END]);
		//closing the pipeB completely since parent doesn't need it.
		close(pipeB[READ_END]);
		close(pipeB[WRITE_END]);

		// calling pWork function.
		pWork(pipeC, pipeA);

		// closing unused ends.
		close(pipeA[WRITE_END]);
		close(pipeC[READ_END]);
		// waiting for child to terminate.
		wait(NULL);
		exit(0);
	}

	return 0;
}


