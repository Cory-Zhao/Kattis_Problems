#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int S, C, K;
    int color;
    int num_machines = 0;
    vector<int> laundry;
    cin >> S >> C >> K;

    for (int i = 0; i < S; i++) {
        cin >> color;
        laundry.push_back(color);
    }

    sort(laundry.begin(), laundry.end());
    
    int machine_index = 0;
    while (S > 0) {
        num_machines += 1;
        
        int lower_bound = laundry.at(machine_index);
        int upper_bound = lower_bound + K;
        int count = 0;
        for (int i = machine_index; i < laundry.size(); i++) {
            if (count == C || laundry.at(i) > upper_bound) {
                machine_index = i;
                //cout << "i: " << i << " | machine_index: " << machine_index << " | lower_bound: " << lower_bound << " | upper_bound: " << upper_bound << " | count: " << count << " | num_machines: " << num_machines << " | S: " << S << endl;
                break;
            }
            else {
                count++;
                S--;
                //cout << "i: " << i << " | machine_index: " << machine_index << " | lower_bound: " << lower_bound << " | upper_bound: " << upper_bound << " | count: " << count << " | num_machines: " << num_machines << " | S: " << S << endl;
            }
        }
    }

    cout << num_machines << endl;
    return 0;
}