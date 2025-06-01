#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int to, cap, rev;
};

int main()
{
    int nLeft, nRight, m;
    cin >> nLeft >> nRight >> m;

    int S = 0;
    int T = nLeft + nRight + 1;
    int N = T + 1;

    vector<vector<Edge>> G(N);
    auto addEdge = [&](int u, int v)
    {
        G[u].push_back({v, 1, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    };

    for (int u = 1; u <= nLeft; ++u)
        addEdge(S, u);

    vector<pair<int, int>> edges;
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        v += nLeft;
        addEdge(u, v);
        edges.emplace_back(u, v);
    }

    for (int v = nLeft + 1; v <= nLeft + nRight; ++v)
        addEdge(v, T);

    int flow = 0;
    while (true)
    {
        vector<int> parent(N, -1), pe(N, -1);
        queue<int> q;
        q.push(S);
        parent[S] = S;

        while (!q.empty() && parent[T] == -1)
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < G[u].size(); ++i)
            {
                Edge &e = G[u][i];
                if (e.cap > 0 && parent[e.to] == -1)
                {
                    parent[e.to] = u;
                    pe[e.to] = i;
                    q.push(e.to);
                }
            }
        }

        if (parent[T] == -1)
            break;

        for (int v = T; v != S;)
        {
            int u = parent[v], i = pe[v];
            G[u][i].cap -= 1;
            G[v][G[u][i].rev].cap += 1;
            v = u;
        }
        ++flow;
    }

    vector<int> matchLeft(nLeft + 1, 0), matchRight(nRight + 1, 0);
    for (int u = 1; u <= nLeft; ++u)
    {
        for (auto &e : G[u])
        {
            if (e.to > nLeft && e.cap == 0)
            {
                int v = e.to - nLeft;
                matchLeft[u] = v;
                matchRight[v] = u;
            }
        }
    }

    vector<vector<int>> fromLeft(nLeft + nRight + 1), fromRight(nLeft + nRight + 1);
    for (auto &[u, v] : edges)
    {
        if (matchLeft[u] == v - nLeft)
        {
            fromRight[v].push_back(u);
            fromLeft[u].push_back(v);
        }
        else
        {
            fromLeft[u].push_back(v);
            fromRight[v].push_back(u);
        }
    }

    vector<char> visLeft(nLeft + nRight + 1, 0), visRight(nLeft + nRight + 1, 0);
    queue<int> q;
    for (int u = 1; u <= nLeft; ++u)
    {
        if (matchLeft[u] == 0)
        {
            visLeft[u] = 1;
            q.push(u);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : fromLeft[u])
        {
            if (!visLeft[v])
            {
                visLeft[v] = 1;
                q.push(v);
            }
        }
    }

    for (int v = 1; v <= nRight; ++v)
    {
        if (matchRight[v] == 0)
        {
            int vv = nLeft + v;
            visRight[vv] = 1;
            q.push(vv);
        }
    }
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u : fromRight[v])
        {
            if (!visRight[u])
            {
                visRight[u] = 1;
                q.push(u);
            }
        }
    }

    string resLeft(nLeft, 'P'), resRight(nRight, 'P');
    for (int u = 1; u <= nLeft; ++u)
        if (!visLeft[u])
            resLeft[u - 1] = 'N';
    for (int v = 1; v <= nRight; ++v)
        if (!visRight[nLeft + v])
            resRight[v - 1] = 'N';

    cout << resLeft << "\n"
         << resRight << "\n";
    return 0;
}
