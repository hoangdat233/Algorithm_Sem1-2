#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H, N;
    cin >> W >> H >> N;

    if (W == 1 && H == 1)
    {
        cout << (N >= 1 ? "Yes" : "No") << "\n";
        return 0;
    }

    if (N == 0)
    {
        cout << "No\n";
        return 0;
    }

    if (1LL * W * H > 5LL * N)
    {
        cout << "No\n";
        return 0;
    }

    vector<pair<int, int>> covered;

    for (int i = 0; i < N; ++i)
    {
        int cx, cy;
        cin >> cx >> cy;

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (abs(dx) + abs(dy) > 1)
                    continue;

                int nx = cx + dx;
                int ny = cy + dy;

                if (nx >= 1 && nx <= W && ny >= 1 && ny <= H)
                {
                    covered.emplace_back(nx, ny);
                }
            }
        }
    }

    sort(covered.begin(), covered.end());
    covered.erase(unique(covered.begin(), covered.end()), covered.end());

    if ((int)covered.size() == W * H)
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}
