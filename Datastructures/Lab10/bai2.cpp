#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct E
{
    int u, v, w;
    bool operator<(const E &o) const
    {
        return w > o.w;
    }
};

struct D
{
    vector<int> p, r;
    D(int n) : p(n), r(n, 0)
    {
        for (int i = 0; i < n; ++i)
            p[i] = i;
    }

    int f(int v)
    {
        if (p[v] == v)
            return v;
        return p[v] = f(p[v]);
    }

    bool u(int a, int b)
    {
        a = f(a);
        b = f(b);
        if (a == b)
            return false;
        if (r[a] < r[b])
            swap(a, b);
        p[b] = a;
        if (r[a] == r[b])
            ++r[a];
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    priority_queue<E> pq;
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        pq.push({--u, --v, w});
    }

    D d(n);
    int cost = 0, cnt = 0;

    while (!pq.empty() && cnt < n - 1)
    {
        E e = pq.top();
        pq.pop();
        if (d.u(e.u, e.v))
        {
            cost += e.w;
            ++cnt;
        }
    }

    cout << cost << "\n";
    return 0;
}
