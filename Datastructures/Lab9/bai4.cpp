#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int from, to, cost;
};

const int INF = 1e9;

int main()
{
    int u, path;
    cin >> u >> path;

    vector<Edge> edges(path);
    for (int i = 0; i < path; i++)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    vector<long long> dist(u + 1, -INF);
    dist[1] = 0;

    for (int i = 1; i <= u - 1; i++)
    {
        for (const auto &edge : edges)
        {
            if (dist[edge.from] != -INF && dist[edge.to] < dist[edge.from] + edge.cost)
            {
                dist[edge.to] = dist[edge.from] + edge.cost;
            }
        }
    }

    vector<bool> loop(u + 1, false);
    for (int i = 1; i <= u - 1; i++)
    {
        for (const auto &edge : edges)
        {
            if (dist[edge.from] != -INF && dist[edge.to] < dist[edge.from] + edge.cost)
            {
                dist[edge.to] = dist[edge.from] + edge.cost;
                loop[edge.to] = true;
            }
            if (loop[edge.from])
                loop[edge.to] = true;
        }
    }

    if (loop[u])
    {
        cout << ":)" << endl;
    }
    else if (dist[u] == -INF)
    {
        cout << ":(" << endl;
    }
    else
    {
        cout << dist[u] << endl;
    }

    return 0;
}