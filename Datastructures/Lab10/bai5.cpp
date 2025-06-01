#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct E
{
    int u, v;
    long long c;
};

void quickSortEdges(vector<E> &arr, int low, int high)
{
    if (low >= high)
        return;
    long long pivot = arr[(low + high) / 2].c;
    int i = low, j = high;
    while (i <= j)
    {
        while (arr[i].c < pivot)
            i++;
        while (arr[j].c > pivot)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++, j--;
        }
    }
    if (low < j)
        quickSortEdges(arr, low, j);
    if (i < high)
        quickSortEdges(arr, i, high);
}

void quickSortInts(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;
    int pivot = arr[(low + high) / 2];
    int i = low, j = high;
    while (i <= j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++, j--;
        }
    }
    if (low < j)
        quickSortInts(arr, low, j);
    if (i < high)
        quickSortInts(arr, i, high);
}

struct D
{
    vector<int> p, r;
    D(int n)
    {
        p.resize(n);
        r.resize(n, 1);
        for (int i = 0; i < n; i++)
            p[i] = i;
    }
    int f(int x)
    {
        return p[x] == x ? x : (p[x] = f(p[x]));
    }
    bool u(int x, int y)
    {
        int xr = f(x), yr = f(y);
        if (xr == yr)
            return false;
        if (r[xr] < r[yr])
            swap(xr, yr);
        p[yr] = xr;
        if (r[xr] == r[yr])
            r[xr]++;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> x(n), y(n), c(n), k(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];
    for (int i = 0; i < n; ++i)
        cin >> c[i];
    for (int i = 0; i < n; ++i)
        cin >> k[i];

    vector<E> es;
    for (int i = 0; i < n; ++i)
    {
        es.push_back({i, n, c[i]});
        for (int j = i + 1; j < n; ++j)
        {
            long long cost = (abs(x[i] - x[j]) + abs(y[i] - y[j])) * 1LL * (k[i] + k[j]);
            es.push_back({i, j, cost});
        }
    }

    quickSortEdges(es, 0, es.size() - 1);

    D d(n + 1);
    long long tc = 0;
    vector<int> st;
    vector<pair<int, int>> cn;

    for (const auto &e : es)
    {
        if (d.u(e.u, e.v))
        {
            tc += e.c;
            if (e.v == n)
                st.push_back(e.u + 1);
            else
                cn.emplace_back(e.u + 1, e.v + 1);
        }
    }

    quickSortInts(st, 0, st.size() - 1);
    cout << tc << "\n";
    cout << st.size() << "\n";
    for (int s : st)
        cout << s << " ";
    cout << "\n";
    cout << cn.size() << "\n";
    for (const auto &c : cn)
        cout << c.first << " " << c.second << "\n";

    return 0;
}
