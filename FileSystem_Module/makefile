#
# PROGRAM:    Assignment 7 makefile
# PROGRAMMER: Dinesh Sandadi.
#

CC = g++
CCFLAGS = -Wall -std=c++11

FileSystem_FAT: FileSystem_FAT.o Entry.o
	$(CC) $(CCFLAGS) -o FileSystem_FAT FileSystem_FAT.o Entry.o
Entry.o: Entry.cpp
	 $(CC) $(CCFLAGS) -c Entry.cpp
FileSystem_FAT.o: FileSystem_FAT.cpp
	$(CC) $(CCFLAGS) -c FileSystem_FAT.cpp
clean:
	-rm *.o FileSystem_FAT
