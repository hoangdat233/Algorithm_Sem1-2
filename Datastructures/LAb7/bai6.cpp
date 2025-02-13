#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    vector<int> lis; 

    for (int i = 0; i < n; i++) {
        auto pos = lower_bound(lis.begin(), lis.end(), heights[i]);
        if (pos == lis.end()) {
            lis.push_back(heights[i]);
        } else {
            *pos = heights[i];
        }
    }

    cout << lis.size() << endl;
    return 0;
}
