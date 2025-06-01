#include <iostream>
using namespace std;

const int M = 1 << 20;

long long keyTable[M];
int valTable[M];
bool usedTable[M];

unsigned int my_hash(long long x)
{
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdLL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53LL;
    x ^= x >> 33;
    return static_cast<unsigned int>(x) & (M - 1);
}

int &get(long long x)
{
    unsigned int pos = my_hash(x);
    while (usedTable[pos] && keyTable[pos] != x)
        pos = (pos + 1) & (M - 1);
    if (!usedTable[pos])
    {
        usedTable[pos] = true;
        keyTable[pos] = x;
        valTable[pos] = 0;
    }
    return valTable[pos];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        get(x)++;
    }

    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        get(x)--;
    }

    for (int i = 0; i < M; ++i)
    {
        if (usedTable[i] && valTable[i] != 0)
        {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
