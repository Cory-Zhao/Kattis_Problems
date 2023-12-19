#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std; 

typedef pair<int, int> prr;
typedef pair<int, bool> edge;

struct Node {
    int index;
    Node* parent;

    Node(int i) {
        index = i;
        parent = nullptr;
    }
};


void FillTreeNodes(vector<Node*>& TreeNodes) {
    for (int i = 1; i < TreeNodes.size(); i++) {
        Node* temp = new Node(i);
        TreeNodes.at(i) = temp;
    }
}


void prims(vector<Node*>& TreeNodes, vector<vector<edge>>& adj_list, int n, int& count_blues) {
    int source_node = 1;
    vector<int> paths(n + 1, INT_MAX);
    vector<bool> visited(n + 1);
    priority_queue<prr, vector<prr>, greater<prr>> pq;

    paths[source_node] = 0;

    pq.push({0, source_node});

    while (!pq.empty()) {
        int curr_path = pq.top().first;
        int curr_node = pq.top().second;

        pq.pop();

        if (visited[curr_node]) {
            continue;
        }

        visited[curr_node] = true;

        if (TreeNodes[curr_node]->parent) {
            int parent = TreeNodes[curr_node]->parent->index;
            adj_list[curr_node][parent].second = true;
            adj_list[parent][curr_node].second = true;
            if (adj_list[curr_node][parent].first == 2) {
                count_blues++;
            }            
        }

        for (int i = 1; i < adj_list[curr_node].size(); i++) {
            edge next_node = adj_list[curr_node][i];
            int weight = next_node.first;
            if (weight != 0) {
                if (!visited[i] && weight < paths[i]) {
                    TreeNodes[i]->parent = TreeNodes[curr_node];
                    paths[i] = weight;

                    pq.push({weight, i});
                }
            }
        }
    }
}

Node* LeastComAncestor(Node* u, Node* v, int n) {
    vector<bool> visited(n + 1);

    while (u) {
        visited[u->index] = true;
        u = u->parent;
    }
    while (!visited[v->index]) {
        v = v->parent;
    }
    return v;

}

bool CheckContainsRed(vector<vector<edge>>& adj_list, Node* descendant, Node* ancestor) {
    while (descendant != ancestor) {
        if (adj_list[descendant->index][descendant->parent->index].first == 1) {
            return true;
        }
        descendant = descendant->parent;
    }
    return false;
}

bool CheckCycle(vector<Node*>& TreeNodes, vector<vector<edge>>& adj_list, int n, int& count_blues, int target) {
    for (int from = 1; from < adj_list.size(); from++) {
        for (int to = 1; to < adj_list[to].size(); to++) {
            edge curr_edge = adj_list[from][to];

            if (curr_edge.second || curr_edge.first != 2) {
                continue;
            }
            else {
                Node* u = TreeNodes[from];
                Node* v = TreeNodes[to];
                Node* ancestor = LeastComAncestor(u, v, n);

                bool u_path = CheckContainsRed(adj_list, u, ancestor);
                bool v_path = CheckContainsRed(adj_list, v, ancestor);
                if (!u_path && !v_path) {
                    continue;
                }
                else if (u_path) {
                    Node* temp = u;
                    Node* next = temp->parent;
                    Node* nextnext;
                    while (temp != ancestor) {
                        if (adj_list[temp->index][next->index].first == 1) {
                            adj_list[temp->index][next->index].second = false;
                            adj_list[next->index][temp->index].second = false;
                            break;
                        }
                        else {
                            nextnext = next->parent;
                            next->parent = temp;

                            temp = next;
                            next = nextnext;
                        }
                    }
                    u->parent = TreeNodes[to];
                }
                else {
                    Node* temp = v;
                    Node* next = temp->parent;
                    Node* nextnext;
                    while (temp != ancestor) {
                        if (adj_list[temp->index][next->index].first == 1) {
                            adj_list[temp->index][next->index].second = false;
                            adj_list[next->index][temp->index].second = false;
                            break;
                        }
                        else {
                            nextnext = next->parent;
                            next->parent = temp;

                            temp = next;
                            next = nextnext;
                        }
                        //not right yet
                    }
                    v->parent = TreeNodes[from];
                }
                adj_list[from][to].second = true;
                adj_list[to][from].second = true;
                count_blues++;
            }

            if (count_blues == target) {
                return true;
            }

        }
    }
    return false;
}

int main() {
    int n, m, k, f, t, weight;
    int count_blues = 0;
    char c;

    cin >> n >> m >> k;

    vector<vector<edge>> adj_list(n + 1, vector<edge>(n + 1));
    vector<Node*> TreeNodes(n + 1);
    FillTreeNodes(TreeNodes);

    for (int i = 0; i < m; i++) {
        //cin >> weight >> f >> t;
        cin >> c >> f >> t;
        if (c == 'B') {
            weight = 2;
        }
        if (c == 'R') {
            weight = 1;
        }


        adj_list[f][t] = {weight, false};
        adj_list[t][f] = {weight, false};
    }

    prims(TreeNodes, adj_list, n, count_blues);


    /*for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            Node* ancestor = LeastComAncestor(TreeNodes, TreeNodes[i], TreeNodes[j]);
            cout << "Nodes: " << i << " and " << j << " | " << "Ancestor Node: " << ancestor->index << endl;
        }
    }*/
   
    /*for (int i = 1; i < TreeNodes.size(); i++) {
        int parent_index = -1;
        int grandparent_index = -2;
        if (TreeNodes[i]->parent) {
            parent_index = TreeNodes[i]->parent->index;
            if (TreeNodes[i]->parent->parent) {
                grandparent_index = TreeNodes[i]->parent->parent->index;
            }
        }
        cout << "Node: " << TreeNodes[i]->index << " | Parent: " << parent_index <<  " | Grandparent: " << grandparent_index << endl;
    }
    cout << "----------------------" << endl;
    for (int row = 1; row < adj_list.size(); row++) {
        for (int col = 1; col < adj_list[row].size(); col++) {
            cout << "{" << adj_list[row][col].first << ", " << adj_list[row][col].second << "}" << " | ";
        }
        cout << endl;
    }*/

    if (count_blues > k) {
        cout << false << endl;
    }
    else if (count_blues == k) {
        cout << true << endl;
    }
    else {
        cout << CheckCycle(TreeNodes, adj_list, n, count_blues, k) << endl;
    }

    return 0;
}