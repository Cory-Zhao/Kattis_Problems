#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums.at(i);
    }

    int length = 0;
    vector<int> LIS(n, 1);
    vector<int> LDS(n, 1);

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (nums.at(j) > nums.at(i)) {
                LIS.at(i) = max(LIS.at(i), LIS.at(j) + 1);
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (nums.at(j) < nums.at(i)) {
                LDS.at(i) = max(LDS.at(i), LDS.at(j) + 1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        length = max(length, LDS.at(i) + LIS.at(i) - 1);
    }
    cout << length << endl;
    return 0;
}