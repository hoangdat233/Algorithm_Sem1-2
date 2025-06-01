#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 100005;
vector<vector<int>> graph(MAXN), reverseGraph(MAXN);
vector<bool> visited(MAXN);
stack<int> order;
int component[MAXN];
vector<vector<int>> components;

void dfs1(int v)
{
    visited[v] = true;
    for (int u : graph[v])
        if (!visited[u])
            dfs1(u);
    order.push(v);
}

void dfs2(int v, int compID)
{
    component[v] = compID;
    components.back().push_back(v);
    visited[v] = true;
    for (int u : reverseGraph[v])
        if (!visited[u])
            dfs2(u, compID);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
        reverseGraph[v].push_back(u);
        edges[i] = make_pair(u, v);
    }

    fill(visited.begin(), visited.begin() + n, false);
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs1(i);

    fill(visited.begin(), visited.begin() + n, false);
    int compID = 0;
    while (!order.empty())
    {
        int v = order.top();
        order.pop();
        if (!visited[v])
        {
            components.push_back({});
            dfs2(v, compID++);
        }
    }

    if (compID == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    set<pair<int, int>> dagEdges;
    vector<int> indeg(compID, 0), outdeg(compID, 0);

    for (size_t i = 0; i < edges.size(); ++i)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        int cu = component[u], cv = component[v];
        if (cu != cv && dagEdges.insert(make_pair(cu, cv)).second)
        {
            outdeg[cu]++;
            indeg[cv]++;
        }
    }

    vector<int> sources, sinks;
    for (int i = 0; i < compID; ++i)
    {
        if (indeg[i] == 0)
            sources.push_back(i);
        if (outdeg[i] == 0)
            sinks.push_back(i);
    }

    int k = max(sources.size(), sinks.size());
    cout << k << endl;

    vector<pair<int, int>> newEdges;
    for (int i = 0; i < k; ++i)
    {
        int from = components[sinks[i % sinks.size()]][0];
        int to = components[sources[i % sources.size()]][0];
        newEdges.push_back({from + 1, to + 1});
    }

    sort(newEdges.begin(), newEdges.end());

    for (auto &edge : newEdges)
    {
        cout << edge.first << " " << edge.second << endl;
    }

    return 0;
}
