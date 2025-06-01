#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e18;

struct Edge
{
    int from, to;
    long long weight;
};

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    s--;

    vector<Edge> edges(m);
    vector<long long> dist(n, INF);
    dist[s] = 0;

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        edges[i].from--;
        edges[i].to--;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (const auto &edge : edges)
        {
            if (dist[edge.from] < INF && dist[edge.from] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }

    vector<bool> neg_cycle(n, false);
    for (int i = 0; i < n; i++)
    {
        for (const auto &edge : edges)
        {
            if (dist[edge.from] < INF && dist[edge.from] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = -INF;
                neg_cycle[edge.to] = true;
            }
            if (neg_cycle[edge.from])
            {
                neg_cycle[edge.to] = true;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (neg_cycle[i])
        {
            cout << "-" << endl;
        }
        else if (dist[i] == INF)
        {
            cout << "*" << endl;
        }
        else
        {
            cout << dist[i] << endl;
        }
    }
    return 0;
}