#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> clan(N + 1);
    for (int i = 1; i <= N; ++i)
        cin >> clan[i];

    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;

        int cost_uv = 0, cost_vu = 0;

        if (clan[u] != clan[v])
        {
            cost_uv = (u % 2 == 0) ? 2 : 1;
            cost_vu = (v % 2 == 0) ? 2 : 1;
        }

        adj[u].push_back(make_pair(v, cost_uv));
        adj[v].push_back(make_pair(u, cost_vu));
    }

    vector<long long> dist(N + 1, INF);
    vector<int> parent(N + 1, -1);
    dist[1] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, 1));

    while (!pq.empty())
    {
        pair<long long, int> top = pq.top();
        pq.pop();
        long long d = top.first;
        int u = top.second;

        if (d > dist[u])
            continue;

        for (size_t i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int cost = adj[u][i].second;
            if (dist[v] > dist[u] + cost)
            {
                dist[v] = dist[u] + cost;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[N] == INF)
    {
        cout << "impossible\n";
    }
    else
    {
        vector<int> path;
        for (int v = N; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());

        cout << dist[N] << " " << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] << " ";
        cout << "\n";
    }

    return 0;
}
