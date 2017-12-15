//
// Created by DINESH on 11/30/2017.
//

#ifndef ASSIGN7_ASSIGN7_H_H
#define ASSIGN7_ASSIGN7_H_H
#include "Entry.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <cmath>
#include <list>
#include <iomanip>


#define BLOCK_SIZE 512
#define HOWOFTEN 6
#define MAX_ENTRIES 12
#define TOTAL_BLOCKS 4096
#define LIMIT 240
using namespace std;

int FATTable[4096];// FAT table with 4096 entries.
list<Entry *> directory;

bool searchFile(string fileName);
void readFile(string path);
void processLine(string line);
void copyFile(string old ,string newFile);
void deleteFile(string fileName);
void createNewFile(string,int);
void modifyFile(string,int);
void renameFile(string old,string newFile);
int populateFatTable(int, int);
void removeFromFatTable(int);
Entry* findFile(string fileName);
void copyFile(string, string);
void printFATTable();
void printDirectory();
void printAllocatedBlocks(int,int);
int findFirstAvailableBlock();
int getTotalSize ();
int findLastBlock(int end);

#endif //ASSIGN7_ASSIGN7_H
