#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll x, ll y)
{
    while (y)
    {
        x %= y;
        swap(x, y);
    }
    return x;
}

ll countWays(ll h, ll a, ll b, ll c)
{
    if (h < 1)
        return 0;
    if (h == 1)
        return 1;

    ll d = gcd(gcd(a, b), c);
    a /= d, b /= d, c /= d;
    ll max_k = (h - 1) / d;

    ll m = min({a, b, c});
    if (m == 1)
        return max_k + 1;

    const ll INF = 1e18;
    vector<ll> dp(m, INF);
    dp[0] = 0;

    queue<ll> q;
    q.push(0);

    vector<ll> steps = {a, b, c};
    while (!q.empty())
    {
        ll r = q.front();
        q.pop();

        for (ll step : steps)
        {
            ll new_r = (r + step) % m;
            if (dp[r] + step < dp[new_r])
            {
                dp[new_r] = dp[r] + step;
                q.push(new_r);
            }
        }
    }

    ll count = 0;
    for (ll r = 0; r < m; r++)
    {
        if (dp[r] <= max_k)
        {
            count += (max_k - dp[r]) / m + 1;
        }
    }
    return count;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    ll h, a, b, c;
    cin >> h >> a >> b >> c;
    cout << countWays(h, a, b, c) << "\n";
    return 0;
}
