#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct Edge
{
    int to, weight;
};

vector<vector<Edge>> adj;

int dijkstra(int N, int S, int F)
{
    vector<int> dist(N + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    dist[S] = 0;
    q.push(make_pair(0, S));

    while (!q.empty())
    {
        pair<int, int> top = q.top();
        q.pop();

        int cur_dist = top.first;
        int u = top.second;

        if (cur_dist > dist[u])
            continue;
        for (const auto &edge : adj[u])
        {
            int v = edge.to, weight = edge.weight;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                q.push(make_pair(dist[v], v));
            }
        }
    }

    return dist[F] == INF ? -1 : dist[F];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, S, F;
    cin >> N >> M >> S >> F;

    adj.resize(N + 1);

    for (int i = 0; i < M; ++i)
    {
        int b, e, w;
        cin >> b >> e >> w;
        adj[b].push_back({e, w});
        adj[e].push_back({b, w});
    }

    cout << dijkstra(N, S, F) << "\n";
    return 0;
}