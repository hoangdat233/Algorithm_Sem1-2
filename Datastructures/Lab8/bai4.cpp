#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Road {
    int from;
    int to;
};

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

void dfs_reverse(int node, vector<vector<int>>& reverse_adj, vector<bool>& visited, vector<int>& component, int family_id) {
    visited[node] = true;
    component[node] = family_id;
    for (int neighbor : reverse_adj[node]) {
        if (!visited[neighbor]) {
            dfs_reverse(neighbor, reverse_adj, visited, component, family_id);
        }
    }
}

void quick_sort(vector<Road>& roads, int left, int right) {
    if (left >= right) return;
    int pivot = left, i = left + 1, j = right;
    while (i <= j) {
        while (i <= right && (roads[i].from < roads[pivot].from || (roads[i].from == roads[pivot].from && roads[i].to < roads[pivot].to))) i++;
        while (j > left && (roads[j].from > roads[pivot].from || (roads[j].from == roads[pivot].from && roads[j].to > roads[pivot].to))) j--;
        if (i < j) swap(roads[i], roads[j]);
    }
    swap(roads[pivot], roads[j]);
    quick_sort(roads, left, j - 1);
    quick_sort(roads, j + 1, right);
}

void remove_duplicates(vector<int>& vec, int max_val) {
    vector<bool> seen(max_val + 1, false);
    vector<int> temp;
    for (int val : vec) {
        if (!seen[val]) {
            seen[val] = true;
            temp.push_back(val);
        }
    }
    vec = temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> reverse_adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        reverse_adj[b].push_back(a);
    }

    vector<bool> visited(n + 1, false);
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, st);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<int> component(n + 1, -1);
    int family_id = 0;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!visited[node]) {
            dfs_reverse(node, reverse_adj, visited, component, family_id);
            family_id++;
        }
    }

    vector<int> family_representa(family_id, -1);
    for (int i = 1; i <= n; ++i) {
        if (family_representa[component[i]] == -1) {
            family_representa[component[i]] = i;
        }
    }

    vector<vector<int>> family_roads(family_id);
    for (int i = 1; i <= n; ++i) {
        for (int neighbor : adj[i]) {
            if (component[i] != component[neighbor]) {
                family_roads[component[i]].push_back(component[neighbor]);
            }
        }
    }

    int cnt = family_id;
    int road_cnt = 0;
    vector<Road> roads;
    for (int i = 0; i < family_id; ++i) {
        remove_duplicates(family_roads[i], family_id - 1);
        road_cnt += family_roads[i].size();
        for (int j : family_roads[i]) {
            Road r;
            r.from = family_representa[i];
            r.to = family_representa[j];
            roads.push_back(r);
        }
    }

    quick_sort(roads, 0, roads.size() - 1);

    cout << cnt << " " << road_cnt << endl;
    for (const auto& road : roads) {
        cout << road.from << " " << road.to << endl;
    }

    return 0;
}