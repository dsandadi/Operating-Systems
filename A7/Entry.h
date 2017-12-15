//
// Created by DINESH on 11/30/2017.
//

#ifndef ASSIGN7_ENTRY_H
#define ASSIGN7_ENTRY_H
#include <string>
using namespace std;

class Entry {
public:
    string time;
    int start;
    int end;
    string fileName;
    int size ;

    Entry(string,int,int, string,int);
};


#endif //ASSIGN7_ENTRY_H
