#
# PROGRAM : Assign2
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/14/2017

CCFLAGS = -g -Wall 

#Rule to link object code files.
Assign2 : Assign2.o
	gcc $(CCFLAGS) -o Assign2 Assign2.o 

#Rule to compile source code files to create object code files.
Assign2.o : Assign2.c Assign2.h
	gcc $(CCFLAGS) -c Assign2.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o Assign2
