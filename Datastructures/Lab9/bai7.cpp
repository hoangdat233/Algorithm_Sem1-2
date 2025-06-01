#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e6;

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> dist(N, vector<int>(N));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> dist[i][j];
            if (dist[i][j] == -1)
            {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 0; k < N; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    int new_dist = dist[i][k] + dist[k][j];
                    if (new_dist < dist[i][j])
                    {
                        dist[i][j] = new_dist;
                    }
                }
            }
        }
    }

    int D = 0;
    int R = INF;
    vector<int> ecc(N, 0);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i != j && dist[i][j] < INF)
            {
                if (dist[i][j] > ecc[i])
                {
                    ecc[i] = dist[i][j];
                }
            }
        }
        if (ecc[i] > D)
        {
            D = ecc[i];
        }
        if (ecc[i] < R)
        {
            R = ecc[i];
        }
    }

    cout << D << endl
         << R << endl;

    return 0;
}