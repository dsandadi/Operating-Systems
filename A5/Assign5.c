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

// including libraries.

#include "Assign5.h"

/*
 * Function : Produce
 * Purpose  : This function is called by the producer thread.
 * Returns  : void* .
 */
void* Produce(void* threadID) {
	int i ;
	// a loop to insert the items.
	for (i = 0; i < P_STEPS; i++) {
		// waiting if buffer is full.
		sem_wait(&NotFull);
		Insert(threadID);// inserting item in to the buffer.
		sem_post(&NotEmpty);// signalling.
		sleep(1);//sleep for 1 milli second.
	}
	pthread_exit(NULL);// exit the thread.
}
/*
 * Function : Insert
 * Purpose  : This function is called by the produce method to insert an item.
 * Returns  : Nothing.
 */
void Insert(void* threadID){
	long id = (long)threadID;
	// grabbing the mutex lock.
	pthread_mutex_lock(&mutex);
	counter ++ ;// incrementing the counter.
	fprintf(stderr,"Producer %ld inserted one item.  Total is now %d\n",id,counter);
	pthread_mutex_unlock(&mutex);// unlocking the mutex.
}
/*
 * Function : Remove
 * Purpose  : This function is called by the consumer thread to remove an item from the bufer.
 * Returns  : Nothing.
 */

void Remove(void* threadID){
	long id = (long)threadID;
	// grabbing the mutex lock.
	pthread_mutex_lock(&mutex);
	counter-- ;// decrementing the counter.
	fprintf(stderr,"Consumer %ld removed one item.   Total is now %d\n",id,counter);
	pthread_mutex_unlock(&mutex);// unlocking the mutex.
}

/*
 * Function : Consume
 * Purpose  : This function is called by the consumer thread.
 * Returns  : void*.
 */

void* Consume(void* threadID) {
	int i;
	for (i = 0; i < C_STEPS; i++) {
		sem_wait(&NotEmpty);//wait if the buffer is empty.
		Remove(threadID);// remove item from the buffer.
		sem_post(&NotFull);// signal not full.
		sleep(1);
	}
	pthread_exit(NULL);// exit the thread.
}
/*
 * Function : main
 * Purpose  : This is the entry point of the program.
 * Returns  : integer value representing the exit status.
 */

int main(int argc, char** argv) {
	fprintf(stdout,"Simulation of Producer and Consumers \n");
	//creating semaphores.
	if (sem_init(&NotFull, 0, BUFFER_SIZE) < 0) {
		fprintf(stderr, "Can't initialize the NotFull semaphore.\n");
		exit(NON_SUCCESS);

	}
	if (sem_init(&NotEmpty, 0, 0)) {
		fprintf(stderr, "Can't initialize the NotEmpty semaphore.\n");
		exit(NON_SUCCESS);

	}
	//create mutex.
	if (pthread_mutex_init(&mutex, NULL)) {
		fprintf(stderr, "Can't initialize the mutex lock.\n");
		exit(NON_SUCCESS);

	}
	//mutex and semaphores have been setup.

	fprintf(stdout,"The semaphores and mutex have been initialized.\n");
	// Creating an array of producer threads, and an array of consumer threads.
	//initializing producer threads and consumer threads.
	pthread_t producerThreads[P_NUMBER];
	pthread_t consumerThreads[C_NUMBER];

	// creating P_NUMBER of producer threads.
	long i;  
	for(i =0;i<P_NUMBER;i++){
		long rc = pthread_create(&producerThreads[i],NULL,Produce,(void*) i);
		if(rc){
			fprintf(stderr,"Error creating producer thread %ld \n",i);
		}
	}
	// creating C_NUMBER of consumer threads.
	for(i = 0;i<C_NUMBER;i++){
		long rc = pthread_create(&consumerThreads[i],NULL,Consume,(void*) i);
		if(rc){
			fprintf(stderr,"Error creating producer thread %ld \n",i);
		} 
	}

	// Waiting for producer threads to join the main thread.
	for (i =0;i<P_NUMBER;i++){
		pthread_join(producerThreads[i],NULL);
	}
	// Waiting for consumer threads to join the main thread.
	for (i =0;i<C_NUMBER;i++){
		pthread_join(consumerThreads[i],NULL);
	}
	fprintf(stdout,"All the producer and consumer threads have been closed.\n");
	// destroy the notFull semaphore.
	sem_destroy(&NotFull);
	sem_destroy(&NotEmpty);// destroy the notEmpty semaphore.
	pthread_mutex_destroy(&mutex);// destroying the mutex lock.
	fprintf(stdout,"The semaphores and mutex have been deleted.\n");
	return (EXIT_SUCCESS);
}

