#
# PROGRAM : Assign3
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/26/2017

CCFLAGS = -g -Wall 

#Rule to link object code files.
z1797942_A3 : MicroShell.o
	gcc $(CCFLAGS) -o z1797942_A3 MicroShell.o 

#Rule to compile source code files to create object code files.
MicroShell.o : MicroShell.c MicroShell.h
	gcc $(CCFLAGS) -c MicroShell.c

#Pseudo target to remove object code and executables.
clean :
	-rm *.o z1797942_A3
