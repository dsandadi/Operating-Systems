#
# PROGRAM:    Assignment 7 makefile
# PROGRAMMER: Dinesh Sandadi.
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign7: Assign7.o Entry.o
	$(CC) $(CCFLAGS) -o Assign7 Assign7.o Entry.o
Entry.o: Entry.cpp
	 $(CC) $(CCFLAGS) -c Entry.cpp
Assign7.o: Assign7.cpp
	$(CC) $(CCFLAGS) -c Assign7.cpp
clean:
	-rm *.o Assign7
