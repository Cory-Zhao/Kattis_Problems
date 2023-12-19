#include "table.h"
#include "obj.h"
#include <string>

using namespace std;

int main() {
    bool success;
    string num_cases, m, n, hash1, hash2;
    int num_words, hash_size, h1, h2;
    cin >> num_cases;
    for (int i = 0; i < stoi(num_cases); i++) {
        cin >> m >> n;
        num_words = stoi(m);
        hash_size = stoi(n);
        HashTable table(hash_size);
        success = true;
        for (int i = 1; i <= num_words; i++) {
            cin >> hash1 >> hash2;
            h1 = stoi(hash1);
            h2 = stoi(hash2);
            HashedObj word_i(i, h1, h2);
            if (!table.insert(word_i)) {
                success = false;
            }
        }
        if (success) {
            cout << "successful hashing" << endl;
        }
        else {
            cout << "rehash necessary" << endl;
        }

        /*for (size_t i = 0; i < table.array.size(); i++) {
            cout << "Bin: " << i << "  |  Word: " << table.array.at(i).element.getWord() << endl;
        }*/
    }

    
}