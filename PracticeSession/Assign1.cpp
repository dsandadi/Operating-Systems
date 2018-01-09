/****************************************
  Assignment - 1
Name    		: Dinesh Sandadi
Zid     		: Z1797942
Section			: 2
DateDue                 : 9/6/2017
TA			: David Wiilams
Purpose			: This program creates three processes
by calling fork() system call twice.
Execution               : make
			 ./Assign1
 ****************************************/


#include "Assign1.h"
/***************************************
main()

purpose :entry point of the program.
returns nothing.
***************************************/

int main(){
	cerr<<"I am the original process. My PID is "<<getpid()<<parentText<< getppid()<<"\n";

	cerr<<"Now we have first fork\n";
	// first fork
	firstFork();

	return 0;
}
/***************************************
secondFork()

purpose : calls the fork system call to create child.
Parameters : None
Returns    : None
***************************************/
void secondFork(){
	pid_t pid2;//pid2 variable.
	//second fork
	cerr<<"Now we have the second fork.\n";
	
	pid2 = fork();// calling the fork system call.
	// if fork fails.
	if(pid2 < 0)
	{
		cerr<<"second fork failed\n";
		exit(-1);
	}

	// grand child process.
	if(pid2 == 0){
		cerr<< gChText << processText << getpid()<< parentText << getppid()<<"\n";
		cerr<< "I am the grand child, about to exit \n";
		exit(0);

	}

	// parent process
	else{
		cerr<<"I am still the child. "<< processText << getpid() <<" "<< parentText <<getppid()<<"\n";
		wait(NULL);//calling the wait system call.waiting for child to terminate.
		cerr <<"I am the child, about to exit \n";
		exit(0);
	}

}
/*********************************************************
firstFork

purpose  : calls the fork system call to create a child process.
Parameters : Nothing
Returns    : None

*********************************************************/
void firstFork(){
	pid_t pid1;
	
	// first fork
	pid1 = fork();//forking the process.

	// if first fork fails, then print the follwing.
	if(pid1 < 0)
	{
		cerr<<"first fork failed\n";
		exit(-1);
	}

	//child process
	if(pid1 == 0){
		cerr<<"I am the child. "<< processText << getpid() << parentText << getppid()<<"\n";
		secondFork();//calling the second fork.

	}
	
	//parent process
	else{
		cerr<<"I am the parent. "<<processText << getpid() << parentText << getppid() <<"\n";
		cerr<<"I am the parent about to call ps \n";
		sleep(2);// calling sleep function.
		system("ps");//Executing system, system call.
		wait(NULL);//waiting for the child to terminate.
		cerr<<"I am the parent, about to exit\n";
		exit(0);
	}
}
