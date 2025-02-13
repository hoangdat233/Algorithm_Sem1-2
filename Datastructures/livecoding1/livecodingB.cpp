#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int max_balance = 100;  
int main() {
    int n;
    cin >> n;

    vector<int> open(max_balance + 1, 0);
    vector<int> close(max_balance + 1, 0);
    int balanced = 0;

    while (n--) {
        string s;
        cin >> s;
        int balance = 0, min_balance = 0;

        for (char c : s) {
            if (c == '(') balance++;
            else balance--;
            min_balance = min(min_balance, balance);
        }

        if (balance == 0 && min_balance >= 0) {
            balanced++; 
        } else if (balance > 0 && min_balance >= 0) {
            if (balance <= max_balance) open[balance]++;
        } else if (balance < 0 && min_balance == balance) {
            if (-balance <= max_balance) close[-balance]++;
        }
    }

    int res = balanced / 2;
    for (int b = 1; b <= max_balance; b++) {
        res += min(open[b], close[b]);
    }

    cout << res << endl;
    return 0;
}
