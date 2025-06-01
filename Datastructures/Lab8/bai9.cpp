#include <iostream>
#include <vector>

using namespace std;

void DFS(int node, vector<bool>& visited, const vector<vector<int>>& adj, int& cnt_edges, bool& has_cycle) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        cnt_edges++;
        if (!visited[neighbor]) {
            DFS(neighbor, visited, adj, cnt_edges, has_cycle);
        } else {
            has_cycle = true;
        }
    }
}

bool is_hydra(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    bool has_cycle = false;
    int cnt_edges = 0;
    int components = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            components++;
            DFS(i, visited, adj, cnt_edges, has_cycle);
        }
    }

    if (components == 1 && has_cycle && cnt_edges == 2 * n) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (is_hydra(n, adj)) {
        cout << "ARCHIMEDES" << endl;
    } else {
        cout <<"EUCLID" << endl;
    }

    return 0;
}