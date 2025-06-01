#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct City
{
    int x, y;
};

double dist(const City &a, const City &b)
{
    return sqrt((a.x - b.x) * 1.0 * (a.x - b.x) + (a.y - b.y) * 1.0 * (a.y - b.y));
}

int main()
{
    int n;
    cin >> n;

    vector<City> cits(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> cits[i].x >> cits[i].y;
    }

    vector<double> min_e(n, 1e9);
    vector<bool> in_m(n, false);
    min_e[0] = 0.0;
    double tot_w = 0.0;

    for (int i = 0; i < n; ++i)
    {
        int v = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!in_m[j] && (v == -1 || min_e[j] < min_e[v]))
            {
                v = j;
            }
        }

        in_m[v] = true;
        tot_w += min_e[v];

        for (int to = 0; to < n; ++to)
        {
            if (!in_m[to])
            {
                double d = dist(cits[v], cits[to]);
                if (d < min_e[to])
                {
                    min_e[to] = d;
                }
            }
        }
    }
    cout.precision(5);
    cout << fixed << tot_w << endl;
    return 0;
}