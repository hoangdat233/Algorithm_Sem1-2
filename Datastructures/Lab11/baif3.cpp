#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct E
{
    int to, cap, rev;
};

void add(vector<vector<E>> &g, int u, int v)
{
    g[u].push_back({v, 1, (int)g[v].size()});
    g[v].push_back({u, 0, (int)g[u].size() - 1});
}

int main()
{
    int a, b, m;
    cin >> a >> b >> m;
    int s = 0, t = a + b + 1, n = t + 1;
    vector<vector<E>> g(n);

    for (int i = 1; i <= a; ++i)
        add(g, s, i);

    vector<pair<int, int>> ed;
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        v += a;
        add(g, u, v);
        ed.push_back({u, v});
    }

    for (int i = a + 1; i <= a + b; ++i)
        add(g, i, t);

    int f = 0;
    while (true)
    {
        vector<int> pre(n, -1), pe(n, -1);
        queue<int> q;
        q.push(s);
        pre[s] = s;

        while (!q.empty() && pre[t] == -1)
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); ++i)
            {
                E &e = g[u][i];
                if (e.cap > 0 && pre[e.to] == -1)
                {
                    pre[e.to] = u;
                    pe[e.to] = i;
                    q.push(e.to);
                }
            }
        }
        if (pre[t] == -1)
            break;

        for (int v = t; v != s;)
        {
            int u = pre[v], i = pe[v];
            g[u][i].cap -= 1;
            g[v][g[u][i].rev].cap += 1;
            v = u;
        }
        ++f;
    }

    vector<int> ml(a + 1), mr(b + 1);
    for (int u = 1; u <= a; ++u)
        for (E &e : g[u])
            if (e.to > a && e.cap == 0)
                ml[u] = e.to - a, mr[e.to - a] = u;

    vector<vector<int>> d1(a + b + 1), d2(a + b + 1);
    for (int i = 0; i < ed.size(); ++i)
    {
        int u = ed[i].first, v = ed[i].second;
        if (ml[u] == v - a)
            d1[v].push_back(u), d2[u].push_back(v);
        else
            d1[u].push_back(v), d2[v].push_back(u);
    }

    vector<char> vl(a + b + 1), vr(a + b + 1);
    queue<int> q;

    for (int u = 1; u <= a; ++u)
        if (!ml[u])
            vl[u] = 1, q.push(u);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int y : d1[x])
            if (!vl[y])
                vl[y] = 1, q.push(y);
    }

    for (int v = 1; v <= b; ++v)
        if (!mr[v])
            vr[v + a] = 1, q.push(v + a);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int y : d2[x])
            if (!vr[y])
                vr[y] = 1, q.push(y);
    }

    string ansL(a, 'P'), ansR(b, 'P');
    for (int i = 1; i <= a; ++i)
        if (!vl[i])
            ansL[i - 1] = 'N';
    for (int i = 1; i <= b; ++i)
        if (!vr[i + a])
            ansR[i - 1] = 'N';

    cout << ansL << "\n"
         << ansR << "\n";
    return 0;
}
