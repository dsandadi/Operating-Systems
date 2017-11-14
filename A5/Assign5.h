/****************************************
  Assignment - 5
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 10/28/2017
TA                      : David Wiilams
Purpose                 : This program implement producer consumer problem solution using semaphores and mutex.
Execution               : make
./Assign5
 ****************************************/

#ifndef ASSIGN5_H
#define ASSIGN5_H

//Defining all constants required for the program.
#define P_NUMBER 6// producer number
#define C_NUMBER 4// consumer number.
#define BUFFER_SIZE 12// buffer size.
#define P_STEPS 4
#define C_STEPS 6
#define NON_SUCCESS -1

//including libraries.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>

//declaring semaphores and mutex to control threads accessing critical section.
sem_t NotFull,NotEmpty ;
pthread_mutex_t mutex;

//Function Prototypes.
void Insert(void* );
void Remove(void* );
void* Produce(void* );
void* Consume(void* );

// global variable to keep track of counter value.
int counter = 0;

#endif /* ASSIGN5_H */

