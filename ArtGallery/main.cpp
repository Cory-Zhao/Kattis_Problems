#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <climits>

using namespace std;

void initialFill(vector<vector<int>>& dp_n, vector<vector<int>>& dp_l, vector<vector<int>>& dp_r, vector<pair<int, int>>& rooms) {
    int sum = 0;
    dp_n.at(0).at(0) = dp_l.at(0).at(0) = dp_r.at(0).at(0) = sum;
    for (int i = 1; i < dp_n.at(0).size(); i++) {
        sum += rooms.at(i - 1).first + rooms.at(i - 1).second;
        dp_n.at(0).at(i) = dp_l.at(0).at(i) = dp_r.at(0).at(i) = sum;
    }
}

void fill(vector<vector<int>>& dp_n, vector<vector<int>>& dp_l, vector<vector<int>>& dp_r, vector<pair<int, int>>& rooms) {
    for (int i = 1; i < dp_n.size(); i++) {
        for (int j = i; j < dp_n.at(i).size(); j++) {
            int left = rooms.at(j - 1).first;
            int right = rooms.at(j - 1).second;

            dp_n.at(i).at(j) = left + right + max({dp_l.at(i).at(j - 1), dp_r.at(i).at(j - 1), dp_n.at(i).at(j - 1)});
            dp_l.at(i).at(j) = right + max({dp_l.at(i - 1).at(j - 1), dp_n.at(i - 1).at(j - 1)});
            dp_r.at(i).at(j) = left + max({dp_r.at(i - 1).at(j - 1), dp_n.at(i - 1).at(j - 1)});
        }
    }
}

void print(vector<vector<int>>& dp) {
    for (auto& row : dp) {
        for (auto& elm : row) {
            cout << elm << " | ";
        }
        cout << endl;
    }
}

int main() {
    int N, k, r1, r2;

    while (true) {
        cin >> N >> k;
        vector<pair<int, int>> rooms;
        if (N == 0 && k == 0) {
            break;
        }

        for (int i = 0; i < N; i++) {
            cin >> r1 >> r2;
            rooms.push_back({r1, r2});
        }

        vector<vector<int>> dp_n(k + 1, vector<int>(N + 1, INT_MIN));
        vector<vector<int>> dp_l(k + 1, vector<int>(N + 1, INT_MIN));
        vector<vector<int>> dp_r(k + 1, vector<int>(N + 1, INT_MIN));
        
        initialFill(dp_n, dp_l, dp_r, rooms);
        fill(dp_n, dp_l, dp_r, rooms);
        /*print(dp_n);
        print(dp_l);
        print(dp_r);*/
        cout << max({dp_n.at(k).at(N), dp_l.at(k).at(N), dp_r.at(k).at(N)}) << endl;
    }

    return 0;
}
