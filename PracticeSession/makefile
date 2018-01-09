#
# PROGRAM : Assign1
# PROGRAMMER :DINESH SANDADI
# LOGONID    :Z1797942
# DUEDATE    :9/6/2017

CCFLAGS = -ansi -Wall -std=c++11

#Rule to link object code files.
Assign1 : Assign1.o
	g++ $(CCFLAGS) -o Assign1 Assign1.o 

#Rule to compile source code files to create object code files.
Assign1.o : Assign1.cpp Assign1.h
	g++ $(CCFLAGS) -c Assign1.cpp

#Pseudo target to remove object code and executables.
clean :
	-rm *.o Assign1
