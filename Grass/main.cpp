#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// sorts by the left point
bool sortbyleft(const pair<double, double>& a, const pair<double, double>& b) {
    return a.first < b.first;
}

// creates the segment ends into a pair by using Pythag
pair<double, double> space(int x, int r, int l, int w) {
    double left_end, right_end;
    double length = sqrt(double(pow(r, 2)) - pow(double(w) / 2, 2));
    left_end = (double(x) - length >= 0) ? double(x) - length : 0;
    right_end = (double(x) + length <= l) ? double(x) + length : l;
    //cout << "(" << left_end << ", " << right_end << ")" << endl;
    return make_pair(left_end, right_end);
}

int main() {
    int n, l, w;
    int x, r;
    
    while(true) {
        string input_line;
        getline(cin, input_line);

        if (input_line.empty()) {
            break;
        }

        istringstream iss(input_line);
        iss >> n >> l >> w;
    
        vector<pair<double, double>> intervals; // holds each segment as a pair 
        int count = 0;
        double left_end = 0; // represents the left bound where all next segments will need to start before the left_end
        double max_right = 0; // represents the farthest to the right any segment can get
        for (int i = 0; i < n; i++) {
            getline(cin, input_line);

            istringstream iss(input_line);
            iss >> x >> r;
            if (r <= w / 2) {   // ignores if the radius is <= half the width
                continue;
            }
            intervals.push_back(space(x, r, l, w));
        }
        sort(intervals.begin(), intervals.end(), sortbyleft);

        int j = 0;

        // Basically the algorithm we discussed. We go through all segments (x,y) where x < left_end and find the max y out of those segments.
        // We change variables and continue this until we either reach the end or we can't reach the end
        while (j < intervals.size() && (intervals.at(j).first < left_end || abs(intervals.at(j).first - left_end) < 0.0005)) {
            while (j < intervals.size() && (intervals.at(j).first < left_end || abs(intervals.at(j).first - left_end) < 0.0005)) {
                if (intervals.at(j).second >= max_right) {
                    max_right = intervals.at(j).second;
                }
                j++;
            }
            count++;
            left_end = max_right;
            if (abs(double(l) - max_right) < 0.0005) {
                break;
            }
        }

        if (abs(double(l) - max_right) < 0.0005) {
            cout << count << endl;
        }
        else {
            cout << -1 << endl;
        }

        /*cout << "--------------------" << endl;
        for (auto& pair : intervals) {
            cout << "(" << pair.first << ", " << pair.second << ")" << endl; 
        }*/
    }
    return 0;
}