//
// Created by DINESH on 11/30/2017.
//

#include "Entry.h"
Entry::Entry(string time, int start, int end, string fileName, int size) {
    this->time = time;
    this->start = start;
    this->end = end;
    this->fileName = fileName;
    this->size = size;
}
