#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

using namespace std; 

struct Node {
    int index;
    Node* parent;

    Node(int i) {
        index = i;
        parent = nullptr;
    }
};

typedef pair<int, int> prr;
typedef pair<int, bool> edge;

unordered_map<int, unordered_map<int, edge>> adj_list;
vector<Node*> TreeNodes;
int blue_count;



void Fill(vector<Node*>& TreeNodes) {
    for (int i = 1; i < TreeNodes.size(); i++) {
        Node* temp = new Node(i);
        TreeNodes.at(i) = temp;
    }
}


void prims(int n) {
    int source_node = 1;

    vector<bool> visited(n + 1);
    vector<int> paths(n + 1, INT_MAX);
    
    priority_queue<prr, vector<prr>, greater<prr>> pq;

    paths[source_node] = 0;

    pq.push({0, source_node});

    while (!pq.empty()) {
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
                blue_count++;
            }            
        }

        for (auto& e : adj_list[curr_node]) {
            int next_node = e.first;
            int weight = e.second.first;

            if (!visited[next_node] && weight < paths[next_node]) {
                TreeNodes[next_node]->parent = TreeNodes[curr_node];
                paths[next_node] = weight;
                pq.push({weight, next_node});
            }
        }
    }
}

Node* LeastComAncestor(Node* u, Node* v) {
    vector<bool> visited(TreeNodes.size());
    Node* n1 = u;
    Node* n2 = v;

    while (n1) {
        visited[n1->index] = true;
        n1 = n1->parent;
    }
    while (!visited[n2->index]) {
        n2 = n2->parent;
    }
    return n2;

}

bool CheckCycle(int target) {
    /*for (int row = 1; row < adj_list.size(); row++) {
        for (int col = 1; col < adj_list[row].size(); col++) {
            edge curr_edge = adj_list[row][col];

            if (curr_edge.second || curr_edge.first != 2 || curr_edge.first == 0) {
                continue;
            }
            else {
                Node* u = TreeNodes[row];
                Node* v = TreeNodes[col];
                Node* ancestor_node = LeastComAncestor(u, v);

                while (u != ancestor_node) {
                    if (adj_list[u->index][u->parent->index].first == 1) {
                        blue_count++;
                        adj_list[u->index][u->parent->index].second = false;
                        adj_list[u->parent->index][u->index].second = false;

                        u->parent = TreeNodes[col];
                        adj_list[u->index][u->parent->index].second = true;
                        adj_list[u->parent->index][u->index].second = true;
                        break;
                    }
                    u = u->parent;
                }
                if (u == ancestor_node) {
                    while (v != ancestor_node) {
                        if (adj_list[v->index][v->parent->index].first == 1) {
                            blue_count++;
                            adj_list[v->index][v->parent->index].second = false;
                            adj_list[v->parent->index][v->index].second = false;

                            v->parent = TreeNodes[row];
                            adj_list[v->index][v->parent->index].second = true;
                            adj_list[v->parent->index][v->index].second = true;
                            break;
                        }
                        v = v->parent;
                    }
                }
                
            }

            if (blue_count == target) {
                return true;
            }

        }
    }
    return false;*/
    for (unordered_map<int, unordered_map<int, edge>>::iterator it1 = adj_list.begin(); it1 != adj_list.end(); it1++) {
        Node* u = TreeNodes[it1->first];
        for (unordered_map<int, edge>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
            Node* v = TreeNodes[it2->first];
            edge curr_edge = it2->second;
        }
    }
            /*if (curr_edge.second || curr_edge.first != 2) {
                continue;
            }
            else {
                Node* ancestor = LeastComAncestor(u, v);

                while (u != ancestor) {
                    if (adj_list[u->index][u->parent->index].first == 1) {
                        adj_list[u->index][u->parent->index].second = false;
                        adj_list[u->parent->index][u->index].second = false;

//I think the main issue is here where we do parents wrong

                        u->parent = v;
                        adj_list[u->index][u->parent->index].second = true;
                        adj_list[u->parent->index][u->index].second = true;
                        blue_count++;
                        break;
                    }  
                }
                if (u == ancestor) {
                    while (v != ancestor) {
                        if (adj_list[v->index][v->parent->index].first == 1) {
                            adj_list[v->index][v->parent->index].second = false;
                            adj_list[v->parent->index][v->index].second = false;

                            v->parent = u;
                            adj_list[v->index][v->parent->index].second = true;
                            adj_list[v->parent->index][v->index].second = true;
                            blue_count++;
                            break;
                        }
                        v = v->parent;
                    }
                }

            }
            if (blue_count == target) {
                return true;
            }
        }
    }*/
    return false;
}

int main() {
    int n, m, k, f, t, weight;
    blue_count = 0;
    char c;

    cin >> n >> m >> k;

    if (k > n - 1) {
        cout << false << endl;
        return 0;
    }



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

    TreeNodes.resize(n + 1);
    Fill(TreeNodes);
    prims(n);


    /*for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            Node* ancestor = LeastComAncestor(tree, tree[i], tree[j]);
            cout << "Nodes: " << i << " and " << j << " | " << "Ancestor Node: " << ancestor->index << endl;
        }
    }*/
   
    
    for (int i = 1; i < TreeNodes.size(); i++) {
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
    for (unordered_map<int, unordered_map<int, edge>>::iterator it1 = adj_list.begin(); it1 != adj_list.end(); it1++) {
        int u = it1->first;
        for (unordered_map<int, edge>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
            int v = it2->first;
            cout << "Edge " << u << " to " << v << " {" << it2->second.first << ", " << it2->second.second << "}" << " | ";
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
    cout << "Blue Count: " << blue_count << endl;
    



    if (blue_count > k) {
        cout << false << endl;
    }
    else if (blue_count == k) {
        cout << true << endl;
    }
    else {
        cout << CheckCycle(k) << endl;
    }

    return 0;
}
