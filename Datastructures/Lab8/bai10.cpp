#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

vector<int> adj[MAXN];
vector<pair<int, int>> doors[MAXN];
int n, m;

bool canReach(int height) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == n) return true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                bool canPass = false;
                for (auto& door : doors[u]) {  
                    if (door.first <= height && height <= door.second) {
                        canPass = true;
                        break;
                    }
                }
                if (canPass) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        doors[i + 1].push_back({l, r});
    }

    int low = 1, high = 1e6, result = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canReach(mid)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (result == -1) {
        cout << -1 << endl;
    } else {
        int count = 0;
        for (int h = 1; h <= result; ++h) {
            if (canReach(h)) {
                count++;
            }
        }
        cout << count << endl;
    }

    return 0;
}
