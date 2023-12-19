#include "obj.h"
#include <iostream>

HashedObj::HashedObj() {
    val = active = alternate = -1;
}

HashedObj::HashedObj(int word, int h1, int h2) : val{word}, active{h1}, alternate{h2} {
}

int HashedObj::getWord() const {
    return val;
}

int HashedObj::getActive() const {
    return active;
}

int HashedObj::getAlternate() const {
    return alternate;
}

void HashedObj::swap() {
    std::swap(active, alternate);
}