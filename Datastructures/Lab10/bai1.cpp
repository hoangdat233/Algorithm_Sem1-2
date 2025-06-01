#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int a, b, w;
};

struct DSU
{
    vector<int> p, r;
    DSU(int n)
    {
        p.resize(n + 1);
        r.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            p[i] = i;
        }
    }

    int find(int x)
    {
        if (p[x] != x)
        {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    bool unite(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry)
        {
            if (r[rx] > r[ry])
            {
                p[ry] = rx;
            }
            else if (r[rx] < r[ry])
            {
                p[rx] = ry;
            }
            else
            {
                p[ry] = rx;
                r[rx]++;
            }
            return true;
        }
        return false;
    }
};

void quicksort(vector<Edge> &e, int l, int r)
{
    if (l >= r)
        return;
    int pivot = e[r].w;
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (e[j].w < pivot)
        {
            i++;
            Edge temp = e[i];
            e[i] = e[j];
            e[j] = temp;
        }
    }
    Edge temp = e[i + 1];
    e[i + 1] = e[r];
    e[r] = temp;
    quicksort(e, l, i);
    quicksort(e, i + 2, r);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<Edge> e(m);

    for (int i = 0; i < m; i++)
    {
        cin >> e[i].a >> e[i].b >> e[i].w;
    }

    quicksort(e, 0, m - 1);
    DSU d(n);

    int cost = 0, used = 0;
    for (int i = 0; i < m; i++)
    {
        if (d.unite(e[i].a, e[i].b))
        {
            cost += e[i].w;
            used++;
            if (used == n - 1)
                break;
        }
    }

    cout << cost << "\n";
    return 0;
}