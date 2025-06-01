#include <iostream>
#include <vector>
using namespace std;

const int M = 1 << 18;

int keyX[M], valX[M];
bool usedX[M];

int keyY[M], valY[M];
bool usedY[M];

int keySX[M], valSX[M];
bool usedSX[M];

int keySY[M], valSY[M];
bool usedSY[M];

inline int hash1(int x)
{
    return (unsigned(x) * 2654435761u) & (M - 1);
}

int &get(int key[], int val[], bool used[], int x)
{
    int pos = hash1(x);
    while (used[pos] && key[pos] != x)
        pos = (pos + 1) & (M - 1);
    if (!used[pos])
    {
        used[pos] = true;
        key[pos] = x;
        val[pos] = 0;
    }
    return val[pos];
}

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> points(N);
    vector<int> distinctX, distinctY;
    distinctX.reserve(N);
    distinctY.reserve(N);

    for (int i = 0; i < N; ++i)
    {
        int x, y;
        cin >> x >> y;
        points[i] = make_pair(x, y);

        int &fx = get(keyX, valX, usedX, x);
        if (fx == 0)
            distinctX.push_back(x);
        fx++;

        int &fy = get(keyY, valY, usedY, y);
        if (fy == 0)
            distinctY.push_back(y);
        fy++;
    }

    int totalX = distinctX.size();
    int totalY = distinctY.size();

    if (totalX <= 3 || totalY <= 3)
    {
        cout << "YES\n";
        return 0;
    }

    for (int i = 0; i < N; ++i)
    {
        int x = points[i].first;
        int y = points[i].second;
        if (get(keyX, valX, usedX, x) == 1)
        {
            get(keySX, valSX, usedSX, y)++;
        }
    }

    for (int i = 0; i < (int)distinctY.size(); ++i)
    {
        int y = distinctY[i];
        if (totalX - get(keySX, valSX, usedSX, y) <= 2)
        {
            cout << "YES\n";
            return 0;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int x = points[i].first;
        int y = points[i].second;
        if (get(keyY, valY, usedY, y) == 1)
        {
            get(keySY, valSY, usedSY, x)++;
        }
    }

    for (int i = 0; i < (int)distinctX.size(); ++i)
    {
        int x = distinctX[i];
        if (totalY - get(keySY, valSY, usedSY, x) <= 2)
        {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}
