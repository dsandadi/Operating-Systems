#
# PROGRAM:    Assignment 4 makefile
# PROGRAMMER: Dinesh Sandadi.
#

CC = g++
CCFLAGS = -Wall -std=c++11

MemoryAllocation: MemoryAllocation.o Block.o
	$(CC) $(CCFLAGS) -o MemoryAllocation MemoryAllocation.o Block.o
Block.o: Block.cpp
	 $(CC) $(CCFLAGS) -c Block.cpp
MemoryAllocation.o: MemoryAllocation.cpp
	$(CC) $(CCFLAGS) -c MemoryAllocation.cpp
clean:
	-rm *.o MemoryAllocation
