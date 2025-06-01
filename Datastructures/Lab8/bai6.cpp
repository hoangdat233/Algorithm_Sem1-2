#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 100000;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, MAX_N);
    queue<int> q;

    dist[1] = 0;
    q.push(1);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int v : adj[u]){
            if (dist[v] == MAX_N){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    vector<int> res;
    for (int i = 1; i <= n; i++){
        if (dist[i] == k){
            res.push_back(i);
        }
    }

    if (res.empty()){
        cout << "NO\n";
    } else {
        for (int i : res){
            cout << i << "\n";
        }
        cout << "\n";
    }

    return 0;
}