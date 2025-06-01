#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

void dijkstra(int N, int S, int F, vector<vector<int>> &graph)
{
    vector<int> dist(N, INF);
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

        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] != -1 && u != v)
            {
                int new_dist = d + graph[u][v];
                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    q.push({new_dist, v});
                }
            }
        }
    }

    cout << (dist[F] == INF ? -1 : dist[F]) << endl;
}

int main()
{
    int N, S, F;
    cin >> N >> S >> F;
    S--;
    F--;

    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> graph[i][j];
        }
    }
    dijkstra(N, S, F, graph);
    return 0;
}