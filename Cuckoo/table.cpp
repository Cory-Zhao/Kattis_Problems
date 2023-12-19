#include "table.h"

HashTable::HashTable(int size) : array(size) {

}

bool HashTable::insert(HashedObj x) {
    HashedObj temp = x;
    int max_dup = 0;
    int word = x.getWord();
    int active = temp.getActive();
    int alternate = temp.getAlternate();
    if (array.at(active).isEmpty == true) {
        array.at(active).element = temp;
        array.at(active).isEmpty = false;
        return true;
    }
    else if (array.at(alternate).isEmpty == true) {
        temp.swap();
        array.at(alternate).element = temp;
        array.at(alternate).isEmpty = false;
        return true;
    }
    else {
        while (max_dup < 5) {
            swap(temp, array.at(temp.getActive()).element);
            if (temp.getWord() == word) {
                max_dup++;
            }
            temp.swap();
            if (array.at(temp.getActive()).isEmpty == true) {
                array.at(temp.getActive()).element = temp;
                array.at(temp.getActive()).isEmpty = false;
                return true;
            }
        }
        
    }
    return false;
}