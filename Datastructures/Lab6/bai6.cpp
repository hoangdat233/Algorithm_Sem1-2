#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long n;
    cin >> n;

    vector<int> primes;

    for (int i = 2; i < 100; i++) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }

    vector<int> result;

    long long k = 1;
    for (int i = 0; i < 30; i++) {
        if (k > n) break;
        result.push_back(primes[i % primes.size()]); 
        k *= (1 << (i + 1)); 
    }

    cout << result.size() << endl;
    for (int prime : result) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}