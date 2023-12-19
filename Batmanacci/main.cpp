#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    unsigned long long K;
    int N;
    cin >> N >> K;

    if (N - 1 > 89) {
        N = (N % 2 == 0) ? 89 : 88;
    }
    vector<string> sequence = {"N", "A"};
    vector<unsigned long long> fib(N);
    
    fib.at(0) = 1;
    fib.at(1) = 1;

    for (int i = 2; i < fib.size(); i++) {
        fib.at(i) = fib.at(i - 2) + fib.at(i - 1);
    }

    
    while (N > 1) {
        if (K > fib.at(N - 2)) {
            K -= fib.at(N - 2);
            N--;
        }
        else {
            N -= 2;
        }
    }
    cout << sequence.at(N) << endl;

    return 0;
}