#
# PROGRAM : ProcessCommunication
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/14/2017

CCFLAGS = -g -Wall 

#Rule to link object code files.
ProcessCommunication : ProcessCommunication.o
	gcc $(CCFLAGS) -o ProcessCommunication ProcessCommunication.o 

#Rule to compile source code files to create object code files.
ProcessCommunication.o : ProcessCommunication.c ProcessCommunication.h
	gcc $(CCFLAGS) -c ProcessCommunication.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o ProcessCommunication
