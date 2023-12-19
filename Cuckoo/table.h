#ifndef TABLE_H
#define TABLE_H

#include "obj.h"
#include <iostream>
#include <vector>

using namespace std;

class HashTable {
    public: 
        HashTable(int size);
        bool insert(HashedObj x);

    private: 
        struct HashEntry {
            HashedObj element;
            bool isEmpty = true;
        };

        vector<HashEntry> array;
};


#endif