#
# PROGRAM:    Assignment 4 makefile
# PROGRAMMER: Dinesh Sandadi.
#

CC = g++
CCFLAGS = -Wall -std=c++11

Assign6: Assign6.o Block.o
	$(CC) $(CCFLAGS) -o Assign6 Assign6.o Block.o
Block.o: Block.cpp
	 $(CC) $(CCFLAGS) -c Block.cpp
Assign6.o: Assign6.cpp
	$(CC) $(CCFLAGS) -c Assign6.cpp
clean:
	-rm *.o Assign6
