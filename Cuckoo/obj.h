#ifndef OBJ_H
#define OBJ_H

#include <iostream>

class HashedObj {
    public:
        HashedObj();
        HashedObj(int word, int h1, int h2);
        int getWord() const;
        int getActive() const;
        int getAlternate() const;
        void swap();

    private: 
        int val;
        int active;
        int alternate;
};

#endif