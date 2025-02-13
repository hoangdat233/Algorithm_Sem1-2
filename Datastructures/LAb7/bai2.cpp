#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string s;
    cin >> s;

    int count[26] = {0};
    for (char c : s) {
        count[c - 'a']++;
    }

    double low[26] = {0.0}, high[26] = {0.0};
    double total = s.size(), current = 0.0;

    for (int i = 0; i < 26; ++i) {
        if (count[i] > 0) {
            low[i] = current;
            high[i] = current + count[i] / total;
            current = high[i];
        }
    }

    double l = 0.0, h = 1.0;

    for (char c : s) {
        int idx = c - 'a';
        double range = h - l;
        h = l + range * high[idx];
        l = l + range * low[idx];
    }

    cout << fixed << setprecision(6) << l << endl;
    return 0;
}
