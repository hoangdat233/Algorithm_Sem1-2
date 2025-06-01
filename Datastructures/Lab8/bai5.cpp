#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1000005;
vector<int> adj[MAX_N];
vector<bool> visited(MAX_N, false);

bool checkcycle(int u, int p) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (checkcycle(v, u)) return true;
        } else if (v != p) {
            return true; 
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (checkcycle(i, -1)) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
    return 0;
}
