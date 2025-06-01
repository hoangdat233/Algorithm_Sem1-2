#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using ull = unsigned long long;

ull generate_hash(int x, const vector<ull> &hval)
{
    return hval[x];
}

vector<int> compress(const vector<int> &data, const vector<int> &base)
{
    vector<int> result(data.size());
    for (size_t i = 0; i < data.size(); ++i)
    {
        result[i] = lower_bound(base.begin(), base.end(), data[i]) - base.begin();
    }
    return result;
}

vector<ull> compute_hash_sums(const vector<int> &arr, int len, const vector<ull> &hval)
{
    vector<ull> hashes;
    if (arr.size() < len)
        return hashes;

    ull hash_sum = 0;
    for (int i = 0; i < len; ++i)
    {
        hash_sum += generate_hash(arr[i], hval);
    }
    hashes.push_back(hash_sum);

    for (size_t i = len; i < arr.size(); ++i)
    {
        hash_sum += generate_hash(arr[i], hval);
        hash_sum -= generate_hash(arr[i - len], hval);
        hashes.push_back(hash_sum);
    }
    return hashes;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vector<int> a_raw(n);
    for (int &x : a_raw)
        cin >> x;

    cin >> m;
    vector<int> b_raw(m);
    for (int &x : b_raw)
        cin >> x;

    vector<int> all_vals = a_raw;
    all_vals.insert(all_vals.end(), b_raw.begin(), b_raw.end());
    sort(all_vals.begin(), all_vals.end());
    all_vals.erase(unique(all_vals.begin(), all_vals.end()), all_vals.end());

    vector<int> a = compress(a_raw, all_vals);
    vector<int> b = compress(b_raw, all_vals);
    int k = all_vals.size();

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ull> hval(k);
    for (int i = 0; i < k; ++i)
    {
        hval[i] = rng();
        if (hval[i] == 0)
            hval[i] = 1;
    }

    int max_common = min(n, m);
    for (int len = max_common; len >= 1; --len)
    {
        vector<ull> hash_a = compute_hash_sums(a, len, hval);
        sort(hash_a.begin(), hash_a.end());

        vector<ull> hash_b = compute_hash_sums(b, len, hval);
        for (ull hb : hash_b)
        {
            if (binary_search(hash_a.begin(), hash_a.end(), hb))
            {
                cout << len << '\n';
                return 0;
            }
        }
    }

    cout << "0\n";
    return 0;
}
