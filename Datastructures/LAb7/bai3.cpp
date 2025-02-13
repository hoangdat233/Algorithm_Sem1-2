#include <iostream>
#include <vector>

using namespace std;

vector<long long> calcProfits(const vector<long long>& row) {
    int n = row.size();
    vector<long long> pre(n + 1, 0), suf(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + row[i - 1];
        suf[i] = suf[i - 1] + row[n - i];
    }

    vector<long long> maxP(n + 1, 0);
    for (int l = 0; l <= n; ++l) {
        for (int r = 0; r <= n - l; ++r) {
            maxP[l + r] = max(maxP[l + r], pre[l] + suf[r]);
        }
    }

    return maxP;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int rows, ops;
    cin >> rows >> ops;

    vector<vector<long long>> profits(rows);

    for (int i = 0; i < rows; ++i) {
        int n;
        cin >> n;
        vector<long long> row(n);
        for (int j = 0; j < n; ++j) {
            cin >> row[j];
        }
        profits[i] = calcProfits(row);
    }

    vector<long long> dp(ops + 1, 0);
    for (int i = 0; i < profits.size(); ++i) {
        const vector<long long>& cur = profits[i];
        for (int j = ops; j >= 0; --j) {
            for (int k = 0; k < cur.size() && k <= j; ++k) {
                dp[j] = max(dp[j], dp[j - k] + cur[k]);
            }
        }
    }

    cout << dp[ops];
    return 0;
}