#include <iostream>
using namespace std;

const int MAX_N = 100000;
struct Node {
    int v;
    Node* next;
};

Node* adj[MAX_N + 1];
bool visited[MAX_N + 1];

void add(int u, int v) {
    Node* node = new Node{v, adj[u]};
    adj[u] = node;

    node = new Node{u, adj[v]};
    adj[v] = node;
}

void dfs(int u) {
    visited[u] = true;
    for (Node* cur = adj[u]; cur; cur = cur->next)
        if (!visited[cur->v]) dfs(cur->v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i);
        }
    }
    cout << count << '\n';
    return 0;
}
