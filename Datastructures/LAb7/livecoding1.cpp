#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void findLost(int W, int N, const vector<int>& weights) {
    int total = 0;
    for (int w : weights) total += w;
    int lost = total - W;

    if (lost == 0) {
        cout << "0\n";
        return;
    }

    vector<bool> dp(lost + 1, false);  
    vector<int> prev(lost + 1, -1); 

    dp[0] = true;  

    // Process each weight
    for (int i = 0; i < N; ++i) {
        for (int w = lost; w >= weights[i]; --w) {
            if (dp[w - weights[i]] && !dp[w]) {
                dp[w] = true;
                prev[w] = i;  // Track the index of the item that contributed to this sum
            }
        }
    }

    if (!dp[lost]) {
        cout << "0\n";
    } else {
        vector<int> result;
        int weight = lost;
        while (weight > 0) {
            int idx = prev[weight];
            result.push_back(idx + 1);  
            weight -= weights[idx];  
        }

        sort(result.begin(), result.end());
        for (int idx : result) {
            cout << idx << " ";
        }
        cout << "\n";
    }
}

int main() {
    int W, N;
    cin >> W >> N;
    vector<int> weights(N);
    for (int &w : weights) cin >> w;
    findLost(W, N, weights);
    return 0;
}
