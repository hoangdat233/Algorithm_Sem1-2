#include <iostream>
#include <vector>
using namespace std;

const int OFFSET = 10000000;
const int MAX_KEY = 20000001;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int &x : numbers)
    {
        cin >> x;
    }

    vector<int> freq(MAX_KEY, 0);
    long long pairCount = 0;

    for (int i = 0; i < n; ++i)
    {
        int key = numbers[i] - i + OFFSET;
        pairCount += freq[key];
        ++freq[key];
    }

    cout << pairCount << '\n';
    return 0;
}
