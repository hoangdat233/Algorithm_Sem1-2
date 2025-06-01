#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;
const int MAX = 1000;

int n;
int wins[21], remaining[21];
int matches[21][21];

int capacity[MAX][MAX], flow[MAX][MAX];
vector<int> adj[MAX];

const int SOURCE = 0;
const int SINK = 1;
const int MATCH_OFFSET = 10;
const int TEAM_OFFSET = 500;

int my_min(int a, int b)
{
    return (a < b) ? a : b;
}

int matchNode(int i, int j)
{
    return MATCH_OFFSET + i * 21 + j;
}

bool bfs(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    q.push(s);
    parent[s] = s;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next] - flow[cur][next] > 0)
            {
                parent[next] = cur;
                if (next == t)
                    return true;
                q.push(next);
            }
        }
    }
    return false;
}

int maxFlow(int s, int t)
{
    vector<int> parent(MAX);
    int totalFlow = 0;

    while (bfs(s, t, parent))
    {
        int cur = t;
        int new_flow = INF;
        while (cur != s)
        {
            int prev = parent[cur];
            new_flow = my_min(new_flow, capacity[prev][cur] - flow[prev][cur]);
            cur = prev;
        }

        cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            flow[prev][cur] += new_flow;
            flow[cur][prev] -= new_flow;
            cur = prev;
        }

        totalFlow += new_flow;
    }

    return totalFlow;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> wins[i];
    for (int i = 0; i < n; ++i)
        cin >> remaining[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matches[i][j];

    int maxWins = wins[0] + remaining[0];

    for (int i = 1; i < n; ++i)
    {
        if (wins[i] > maxWins)
        {
            cout << "NO\n";
            return 0;
        }
    }

    for (int i = 0; i < MAX; ++i)
    {
        for (int j = 0; j < MAX; ++j)
            capacity[i][j] = flow[i][j] = 0;
        adj[i].clear();
    }

    int totalMatch = 0;

    for (int i = 1; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matches[i][j] == 0)
                continue;

            int mNode = matchNode(i, j);
            int tNode1 = TEAM_OFFSET + i;
            int tNode2 = TEAM_OFFSET + j;

            capacity[SOURCE][mNode] = matches[i][j];
            adj[SOURCE].push_back(mNode);
            adj[mNode].push_back(SOURCE);

            capacity[mNode][tNode1] = matches[i][j];
            capacity[mNode][tNode2] = matches[i][j];
            adj[mNode].push_back(tNode1);
            adj[mNode].push_back(tNode2);
            adj[tNode1].push_back(mNode);
            adj[tNode2].push_back(mNode);

            totalMatch += matches[i][j];
        }
    }
    for (int i = 1; i < n; ++i)
    {
        int tNode = TEAM_OFFSET + i;
        int maxWin = maxWins - wins[i];
        if (maxWin < 0)
            maxWin = 0;

        capacity[tNode][SINK] = maxWin;
        adj[tNode].push_back(SINK);
        adj[SINK].push_back(tNode);
    }

    int flowResult = maxFlow(SOURCE, SINK);
    if (flowResult == totalMatch)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
