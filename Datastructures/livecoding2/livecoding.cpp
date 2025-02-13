#include <iostream>
#include <vector>

using namespace std;

long long countTowers(int N) {
    vector<vector<long long>> dp(N + 1, vector<long long>(N + 1, 0));

    for (int j = 0; j <= N; ++j) {
        dp[0][j] = 1;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            dp[i][j] = dp[i][j - 1]; 
            if (i >= j) {
                dp[i][j] += dp[i - j][j - 1]; 
            }
        }
    }
    return dp[N][N - 1];
}

int main() {
    int N;
    cin >> N; 
    cout << countTowers(N) << endl; 
    return 0;
}
