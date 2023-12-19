#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;

unordered_map<int, int> compute_hash(unordered_map<int, int>& table, int mod) {
    unordered_map<int, int> hashed_table;
    for (unordered_map<int, int>::iterator it = table.begin(); it != table.end(); it++) {
        int hash_value = it->first;
        int num_occurences = it->second;

        for (int i = 1; i <= 26; i++) {
            int val = ((33 * hash_value) ^ i) % mod;
            if (hashed_table.find(val) == hashed_table.end()) {
                hashed_table[val] = num_occurences;
            }
            else {
                hashed_table[val] += num_occurences;
            }
        }
    }

    

    return hashed_table;
}


unordered_map<int, int> backwards_traversal(unordered_map<int, int>& accepted_vals, int mod) {

}


int main() {
    string n, k, m;
    int word_len, hash_val, mod;
    cin >> n >> k >> m;
    word_len = stoi(n);
    hash_val = stoi(k);
    mod = pow(2, stoi(m));


    unordered_map<int, int> hash_table = {{0, 1}};
    unordered_map<int, int> temp;
    for (int i = 0; i < floor(word_len); i++) {
        temp = compute_hash(hash_table, mod);
        hash_table = temp;
        
        
        /*for (unordered_map<int, int>::iterator it = hash_table.begin(); it != hash_table.end(); it++) {
            cout << "Key: " << it->first << "    |    Value: " << it->second << endl;
        }
        cout << endl << endl;*/
    }
    
    for (int i = 0; i < ceil(word_len); i++) {

    }






    /*
    if (hash_table.find(hash_val) == hash_table.end()) {
        cout << "0" << endl;
    }
    else {
        cout << hash_table[hash_val] << endl;
    }
    */
    return 0;
}