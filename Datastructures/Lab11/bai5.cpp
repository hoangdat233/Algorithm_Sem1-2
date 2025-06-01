#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int N, M, w, b, g;

struct Edge
{
    int to, rev;
    int cap;
};

vector<vector<Edge>> graph;
vector<int> level, iter;

void add_edge(int from, int to, int cap)
{
    graph[from].push_back({to, (int)graph[to].size(), cap});
    graph[to].push_back({from, (int)graph[from].size() - 1, 0});
}

void bfs(int s)
{
    level.assign(graph.size(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto &e : graph[v])
        {
            if (e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int upTo)
{
    if (v == t)
        return upTo;
    for (int &i = iter[v]; i < graph[v].size(); i++)
    {
        Edge &e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to])
        {
            int d = dfs(e.to, t, min(upTo, e.cap));
            if (d > 0)
            {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0;
    while (true)
    {
        bfs(s);
        if (level[t] < 0)
            break;
        iter.assign(graph.size(), 0);
        int f;
        while ((f = dfs(s, t, INF)) > 0)
        {
            flow += f;
        }
    }
    return flow;
}

int main()
{
    cin >> N >> M >> w >> b >> g;
    vector<string> picture(N);
    for (int i = 0; i < N; i++)
        cin >> picture[i];

    int size = N * M;
    int S = size;
    int T = size + 1;
    graph.resize(size + 2);

    auto index = [&](int x, int y)
    { return x * M + y; };

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int v = index(i, j);

            if (picture[i][j] == 'B')
                add_edge(S, v, 0);
            else
                add_edge(S, v, b);

            if (picture[i][j] == 'W')
                add_edge(v, T, 0);
            else
                add_edge(v, T, w);

            int dx[] = {1, 0};
            int dy[] = {0, 1};
            for (int d = 0; d < 2; d++)
            {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M)
                {
                    int u = index(ni, nj);
                    add_edge(v, u, g);
                    add_edge(u, v, g);
                }
            }
        }
    }

    int result = max_flow(S, T);
    cout << result << endl;
    return 0;
}
