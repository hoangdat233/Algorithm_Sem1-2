#include <iostream>
using namespace std;

const int MAX_N = 1000000;

struct Node {
    int data;
    Node* next;
};

Node* adj[MAX_N + 1], *rev[MAX_N + 1];
bool visited[MAX_N + 1];
int cmp[MAX_N + 1], stk[MAX_N + 1], top;
int cmpCount;

void add(Node* adj[], int u, int v) {
    Node* newNode = new Node{v, adj[u]};
    adj[u] = newNode;
}

void dfs1(int node) {
    visited[node] = true;
    for (Node* cur = adj[node]; cur; cur = cur->next)
        if (!visited[cur->data]) dfs1(cur->data);
    stk[top++] = node;
}

void dfs2(int node) {
    cmp[node] = cmpCount;
    for (Node* cur = rev[node]; cur; cur = cur->next)
        if (cmp[cur->data] == -1) dfs2(cur->data);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(adj, u, v);
        add(rev, v, u);
    }
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs1(i);

    for (int i = 1; i <= n; i++) cmp[i] = -1;

    for (int i = top - 1; i >= 0; i--)
        if (cmp[stk[i]] == -1) {
            cmpCount++;
            dfs2(stk[i]);
        }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (cmp[a] == cmp[b] ? "YES\n" : "NO\n");
    }
    return 0;
}
