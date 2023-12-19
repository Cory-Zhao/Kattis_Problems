#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

void printSchedule(vector<vector<int>>& schedule) {
    for (int i = 0; i < schedule.size(); i++) {
        cout << "Index: " << i << " [";
        for (int j = 0; j < schedule.at(i).size(); j++) {
            cout << schedule.at(i).at(j) << " ";
        }
        cout << "]" << endl;
    }
}

int maxAmount(priority_queue<int, vector<int>, greater<int>>& accountValues) {
    int sum = 0;
    while (!accountValues.empty()) {
        sum += accountValues.top();
        accountValues.pop();
    }
    return sum;
}

int main() {
    int N, T;
    int c, t;
    cin >> N >> T;
    vector<vector<int>> schedule(T);
    priority_queue<int, vector<int>, greater<int>> accountValues;

    for (int i = 0; i < N; i++) {
        cin >> c >> t;
        schedule.at(t).push_back(c);
    }

    for (int i = 0; i < schedule.size(); i++) {
        sort(schedule.at(i).begin(), schedule.at(i).end());
    }

    for (int i = 0; i < T; i++) {
        if (schedule.at(i).size() == 0) {
            accountValues.push(0);
        }
        else {
            accountValues.push(schedule.at(i).back());
            schedule.at(i).pop_back();
            while (schedule.at(i).size() > 0) {
                if (schedule.at(i).back() < accountValues.top()) {
                    break;
                }
                else {
                    accountValues.pop();
                    accountValues.push(schedule.at(i).back());
                    schedule.at(i).pop_back();
                }
            }
        }
    }
    
    cout << maxAmount(accountValues) << endl;
    return 0;
}