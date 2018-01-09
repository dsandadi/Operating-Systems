#
# PROGRAM : Assign3
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/26/2017

CCFLAGS = -pthread -g -Wall 
CC = gcc
#Rule to link object code files.
Synchronization_Process : Synchronization_Process.o
	$(CC) $(CCFLAGS) -o Synchronization_Process Synchronization_Process.o 

#Rule to compile source code files to create object code files.
Synchronization_Process.o : Synchronization_Process.c Synchronization_Process.h
	$(CC) $(CCFLAGS) -c Synchronization_Process.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o Synchronization_Process
