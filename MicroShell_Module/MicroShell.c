
/****************************************
  Assignment - 3
Name                    : Dinesh Sandadi
Zid                     : Z1797942
Section                 : 2
DateDue                 : 9/26/2017
TA                      : David Wiilams
Purpose                 : This program creates mini shell that executes 
user commands
Execution               : make
./Assign3
 ****************************************/


#include "MicroShell.h"


/**************************************************
Function : removeWhiteSpaces
Purpose  : Removes white spaces from the given string and 
returns the string.
Arguments : input string.
Return     : pointer to the trimmed string.

 ***************************************************/


char* removeWhiteSpaces(char* source) {
	// if source is null return null.
	if (source == NULL) return source;

	char* end;
	end = source + strlen(source) - 1;// initializing the end pointer.

	char* start;
	start = source;// initializing the start pointer.
	// remove trailing zeros.
	while (end > source && isspace(*end)) end--;
	int len = end - source + 1;
	source[len] = '\0';// appending null character at the end.

	// remove leading zeros

	while (start < end && isspace((*start))) start++;// incrementing the start pointer.

	return start;

}

/**************************************************
Function : parseCommand.
Purpose :  parses the command according to given delimiter.
Arguments : command , delimiter, and values
Return    : Number of parsed strings.

 ***************************************************/


int parseCommand(char* command, char* delimiter, char** values) {

	if (strcmp(command, "") == 0) return 0;// if command is empty returns  0
	int index = 0;// initializing the index.

	char* temparg1 = strtok(command, delimiter);
	temparg1 = removeWhiteSpaces(temparg1);// trim white spaces from the tempArg1.
	// initializing the values array.
	values[index++] = temparg1;

	char * ptr;
	char* temparg2 = NULL;
	// initializing the values array of strings.
	while ((ptr = strtok(NULL, delimiter)) != NULL) {
		temparg2 = ptr;
		temparg2 = removeWhiteSpaces(temparg2);// remove white spaces from tempArg2.
		if (temparg2 != NULL) {
			values[index] = temparg2;
			index++;
		}

	}

	return index;
}

/**************************************************
Function : main()
Purpose : Entry point of the program.
Arguments : argument count and string of argv values.
Return   : integer value.

 ***************************************************/

int main(int argc, char** argv) {
	// declaring the variables required for the program.	
	char buff[BUFFER_SIZE];
	char* pipeArray[PIPE_SIZE];// pipeArray consits of two parsed arguments of pipe command.
	char* argArray1[ARGS_SIZE];// argArray1 has parse commands of first argument. 
	char* argArray2[ARGS_SIZE];// argArray2 has parse commands of first argument.

	// processIds of child and grand child processes.
	pid_t pid1;
	pid_t pid2;


	//This loop runs for ever until end of file is typed.
	fprintf(stderr, "480shell> ");

	while (fgets(buff, BUFFER_SIZE, stdin) != NULL) {
		buff[strlen(buff) - 1] = 0;


		if(strcmp (buff, "") == 0){ 
			goto empty;}
		if(strcmp(buff,"q") == 0||(strcmp(buff,"quit")== 0)) exit(0);

		// clearing allthe arrys for safety.
		bzero(pipeArray,PIPE_SIZE);
		bzero(argArray1,ARGS_SIZE);
		bzero(argArray2,ARGS_SIZE);

		// parsing the command for getting both arguments of pipe.
		int len1 = parseCommand(buff, PIPE, pipeArray);
		// variable to hold both the length arguments.
		int len_Args1;
		int len_Args2;

		// parse first argument.
		len_Args1 = parseCommand(pipeArray[0], " ", argArray1);

		// if length greater than 1.
		if(len1 > 1)
			len_Args2 = parseCommand(pipeArray[1], " ",argArray2);
		//setting the last character to null.
		argArray1[len_Args1] = NULL;
		argArray2[len_Args2] = NULL;

		// if first element of argArray1 is not empty.
		if (strcmp(argArray1[0], "") != 0) {

			// fork the process.
			if ((pid1 = fork()) < 0)
				fprintf(stderr, "Fork failed.\n");

			else {
				// fork succeds.
				if (pid1 > 0) {
					/*Parent process.*/
					// waits for child to change state.
					if ((pid1 = waitpid(pid1,NULL,0)) < 0){
						fprintf(stderr, "Error in wait");
					}
				} else {

					/*Child process*/
					int pipeA[2];
					// calls pipe command.
					if (pipe(pipeA) < 0) {
						fprintf(stderr, "PipeA could not be created");
						exit(127);
					}


					// if argument2 is null then executes the command directly.
					if (argArray2[0] == NULL) {

						execvp(argArray1[0], argArray1);
						fprintf(stdout, " Could not execute the command\n");

						exit(127);// if  command can't be executed.
					}

					else {
						// argument 2 is not null. Here pipe comes in to picture.
						if ((pid2 = fork()) < 0)
							fprintf(stderr, "Fork failed.\n");

						else {

							if (pid2 == 0) {
								/*Grand Child process*/
								/* This excutes the instructions before pipe.*/
								// closing stdout, which corresponds to lowest file descriptor.
								fclose(stdout);

								// duplicating pipeA write end make pipeA write end accessible
								//by id of stdout file.

								dup(pipeA[WRITE_END]);
								// closing both read and write end of pipeA.
								close(pipeA[WRITE_END]);
								close(pipeA[READ_END]);

								// executes the argArray1 command.
								execvp(argArray1[0], argArray1);
								fprintf(stderr, "Grand child Couldn't execute");
								exit(127);// if execv fails.

								/*Waits for the grand child process to exit.*/


							} else {
								if (strcmp(argArray2[0], "") == 0) exit(0); // if arg2 is empty.
								/*child process. executes the instruction after the pipe.*/

								// waits for the grand parent process to complete its execution.	
								if ((pid2 = waitpid(pid2,NULL,0) < 0)) {
									fprintf(stderr, "\n I am child Error in wait\n");
								}

								// closing stdin Read end which closes the stdin and makes it available.

								fclose(stdin);

								dup(pipeA[READ_END]);// assigns pipeA read end to stdin.
								// Closing the entire pipe now.
								close(pipeA[READ_END]);
								close(pipeA[WRITE_END]);

								// executes the argArray2.
								execvp(argArray2[0], argArray2);
								fprintf(stderr, "Child Couldn't execute");
								exit(127);//exits if execv fails.
							}
						}
					}

				}
			}
		}

empty: 
		fprintf(stderr, "480shell> ");// prompt.
		bzero(buff,1024);// clear the buffer.
	}
	exit(0);// exit succesfully.

}


