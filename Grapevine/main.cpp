#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Person {
    string name;
    int skepticism;
    int daysLeft;
};

int spreadRumor(const string& source, int days, unordered_map<string, Person>& people, unordered_map<string, unordered_set<string>>& connections) {
    queue<string> q;
    q.push(source);
    people[source].daysLeft = days;

    int heardCount = 0;

    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        if (people[curr].daysLeft == 0)
            continue;

        for (const string& neighbor : connections[curr]) {
            Person& neighborPerson = people[neighbor];

            if (neighborPerson.skepticism > 0) {
                neighborPerson.skepticism--;
                if (neighborPerson.skepticism == 0) {
                    q.push(neighbor);
                    neighborPerson.daysLeft = people[curr].daysLeft - 1;
                    heardCount++;
                }
            }
        }
    }

    return heardCount;
}

int main() {
    int n, m, d;
    cin >> n >> m >> d;

    unordered_map<string, Person> people;
    unordered_map<string, unordered_set<string>> connections;

    for (int i = 0; i < n; i++) {
        string name;
        int skepticism;
        cin >> name >> skepticism;
        people[name] = {name, skepticism, 0};
    }

    for (int i = 0; i < m; i++) {
        string u, v;
        cin >> u >> v;
        connections[u].insert(v);
        connections[v].insert(u);
    }

    string rumorSource;
    cin >> rumorSource;

    int heardCount = spreadRumor(rumorSource, d, people, connections);

    cout << heardCount << endl;

    return 0;
}
