#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using ll = long long;

const ll INF = 1e12;

struct Edge
{
    int to, rev;
    ll capacity;
};

struct Discount
{
    int mod1, mod2;
    ll discount_price;
};

vector<vector<Edge>> adj_list;

void add_edge(int from, int to, ll capacity)
{
    adj_list[from].push_back({to, (int)adj_list[to].size(), capacity});
    adj_list[to].push_back({from, (int)adj_list[from].size() - 1, 0});
}

ll find_augmenting_path(int source, int sink, vector<int> &parent, vector<int> &edgeIdx)
{
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    q.push(source);
    parent[source] = source;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj_list[u].size(); ++i)
        {
            Edge &e = adj_list[u][i];
            if (e.capacity > 0 && parent[e.to] == -1)
            {
                parent[e.to] = u;
                edgeIdx[e.to] = i;
                if (e.to == sink)
                    return 1;
                q.push(e.to);
            }
        }
    }
    return 0;
}

ll edmonds_karp(int source, int sink, int n)
{
    ll total_flow = 0;
    vector<int> parent(n), edgeIdx(n);
    while (find_augmenting_path(source, sink, parent, edgeIdx))
    {
        ll path_flow = INF;
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v], ei = edgeIdx[v];
            path_flow = min(path_flow, adj_list[u][ei].capacity);
        }
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v], ei = edgeIdx[v];
            adj_list[u][ei].capacity -= path_flow;
            int rev = adj_list[u][ei].rev;
            adj_list[v][rev].capacity += path_flow;
        }
        total_flow += path_flow;
    }
    return total_flow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, P;
    cin >> N >> M >> P;

    vector<ll> delivery_profit(N);
    vector<vector<int>> required_modules(N);
    for (int i = 0; i < N; ++i)
    {
        int k;
        cin >> delivery_profit[i] >> k;
        required_modules[i].resize(k);
        for (int &mod : required_modules[i])
        {
            cin >> mod;
            --mod;
        }
    }

    vector<ll> module_cost(M);
    for (ll &c : module_cost)
        cin >> c;

    vector<Discount> discounts(P);
    for (int i = 0; i < P; ++i)
    {
        int a, b;
        ll d;
        cin >> a >> b >> d;
        discounts[i] = {a - 1, b - 1, d};
    }

    int deliveryStart = 0;
    int moduleStart = deliveryStart + N;
    int discountStart = moduleStart + M;
    int source = discountStart + P;
    int sink = source + 1;
    int totalNodes = sink + 1;

    adj_list.assign(totalNodes, vector<Edge>());

    ll sumPositiveFlow = 0;

    for (int i = 0; i < N; ++i)
    {
        int deliveryNode = deliveryStart + i;
        ll profit = delivery_profit[i];
        if (profit >= 0)
        {
            add_edge(source, deliveryNode, profit);
            sumPositiveFlow += profit;
        }
        else
        {
            add_edge(deliveryNode, sink, -profit);
        }
    }
    for (int j = 0; j < M; ++j)
    {
        int moduleNode = moduleStart + j;
        ll cost = -module_cost[j];
        if (cost >= 0)
        {
            add_edge(source, moduleNode, cost);
            sumPositiveFlow += cost;
        }
        else
        {
            add_edge(moduleNode, sink, -cost);
        }
    }

    for (int i = 0; i < P; ++i)
    {
        int discountNode = discountStart + i;
        int a = discounts[i].mod1;
        int b = discounts[i].mod2;
        ll discountValue = module_cost[a] + module_cost[b] - discounts[i].discount_price;

        if (discountValue >= 0)
        {
            add_edge(source, discountNode, discountValue);
            sumPositiveFlow += discountValue;
        }
        else
        {
            add_edge(discountNode, sink, -discountValue);
        }

        add_edge(discountNode, moduleStart + a, INF);
        add_edge(discountNode, moduleStart + b, INF);
    }

    for (int i = 0; i < N; ++i)
    {
        int deliveryNode = deliveryStart + i;
        for (int mod : required_modules[i])
        {
            int moduleNode = moduleStart + mod;
            add_edge(deliveryNode, moduleNode, INF);
        }
    }

    ll max_flow = edmonds_karp(source, sink, totalNodes);
    ll max_profit = sumPositiveFlow - max_flow;

    cout << max_profit << '\n';
    return 0;
}
