#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

void dijkstra(int N, int M, int S, int F, vector<vector<pair<int, int>>> &adj)
{
    vector<int> dist(N + 1, INF);
    vector<int> parent(N + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    dist[S] = 0;
    q.push({0, S});

    while (!q.empty())
    {
        int d = q.top().first;
        int u = q.top().second;
        q.pop();

        if (d > dist[u])
            continue;

        for (size_t i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            int new_dist = d + w;
            if (new_dist < dist[v])
            {
                dist[v] = new_dist;
                parent[v] = u;
                q.push({new_dist, v});
            }
        }
    }

    if (dist[F] == INF)
    {
        cout << -1 << endl;
        return;
    }

    cout << dist[F] << endl;

    vector<int> path;
    for (int v = F; v != -1; v = parent[v])
    {
        path.push_back(v);
    }

    for (size_t i = 0, j = path.size() - 1; i < j; i++, j--)
    {
        swap(path[i], path[j]);
    }

    for (int v : path)
    {
        cout << v << " ";
    }
    cout << endl;
}

int main()
{
    int N, M, S, F;
    cin >> N >> M;
    cin >> S >> F;

    vector<vector<pair<int, int>>> adj(N + 1);

    for (int i = 0; i < M; i++)
    {
        int b, e, w;
        cin >> b >> e >> w;
        adj[b].push_back({e, w});
        adj[e].push_back({b, w});
    }
    dijkstra(N, M, S, F, adj);
    return 0;
}