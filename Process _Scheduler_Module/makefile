#
# PROGRAM:    Assignment 4 makefile
# PROGRAMMER: Dinesh Sandadi.
#

CC = g++
CCFLAGS = -Wall -std=c++11

Scheduler: Scheduler.o Process.o
	$(CC) $(CCFLAGS) -o Scheduler Scheduler.o Process.o
Process.o: Process.cpp
	 $(CC) $(CCFLAGS) -c Process.cpp
Scheduler.o: Scheduler.cpp
	$(CC) $(CCFLAGS) -c Scheduler.cpp
clean:
	-rm *.o Scheduler
