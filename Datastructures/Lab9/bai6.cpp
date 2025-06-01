#include <iostream>
#include <vector>
using namespace std;

struct Ex
{
    int from, to;
    double r, c;
};

int main()
{
    int n, m, s;
    double v;
    cin >> n >> m >> s >> v;

    vector<Ex> exs;
    vector<double> bal(n + 1, 0.0);
    bal[s] = v;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        double rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;

        exs.push_back({a, b, rab, cab});
        exs.push_back({b, a, rba, cba});
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (const auto &ex : exs)
        {
            if (bal[ex.from] > ex.c)
            {
                double new_value = (bal[ex.from] - ex.c) * ex.r;
                if (new_value > bal[ex.to])
                {
                    bal[ex.to] = new_value;
                }
            }
        }
    }

    for (const auto &ex : exs)
    {
        if (bal[ex.from] > ex.c)
        {
            double new_value = (bal[ex.from] - ex.c) * ex.r;
            if (new_value > bal[ex.to])
            {
                cout << "YES" << endl;
                return 0;
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
