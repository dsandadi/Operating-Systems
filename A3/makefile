#
# PROGRAM : Assign3
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/26/2017

CCFLAGS = -g -Wall 

#Rule to link object code files.
z1797942_A3 : Assign3.o
	gcc $(CCFLAGS) -o z1797942_A3 Assign3.o 

#Rule to compile source code files to create object code files.
Assign3.o : Assign3.c Assign3.h
	gcc $(CCFLAGS) -c Assign3.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o z1797942_A3
