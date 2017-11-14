#
# PROGRAM : Assign3
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/26/2017

CCFLAGS = -pthread -g -Wall 
CC = gcc
#Rule to link object code files.
Assign5 : Assign5.o
	$(CC) $(CCFLAGS) -o Assign5 Assign5.o 

#Rule to compile source code files to create object code files.
Assign5.o : Assign5.c Assign5.h
	$(CC) $(CCFLAGS) -c Assign5.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o Assign5
