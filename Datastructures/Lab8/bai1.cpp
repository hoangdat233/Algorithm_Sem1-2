#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX_N = 100000;
vector<int> graph[MAX_N + 1];
bool visited[MAX_N + 1];
int rankN[MAX_N + 1];
stack<int> st;

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    st.push(u);
}

void Sort(int N) {
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    int rank = 1;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        rankN[u] = rank++;
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    Sort(N);
    for (int i = 1; i <= N; i++) {
        cout << rankN[i] << " ";
    }
    cout << endl;
    return 0;
}
