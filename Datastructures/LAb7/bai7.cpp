#include <iostream>
#include <string>
using namespace std;

bool canBuy(const string& pavel, const string& vanya, long long k) {
    int i = 0, j = 0;
    char pavelChar, vanyaChar;
    long long pavelCount = 0, vanyaCount = 0, diff = 0;

    while (i < pavel.size() || j < vanya.size()) {
        if (pavelCount == 0) {
            pavelChar = pavel[i++];
            while (i < pavel.size() && isdigit(pavel[i])) {
                pavelCount = pavelCount * 10 + (pavel[i++] - '0');
            }
            if (pavelCount == 0) pavelCount = 1;
        }

        if (vanyaCount == 0) {
            vanyaChar = vanya[j++];
            while (j < vanya.size() && isdigit(vanya[j])) {
                vanyaCount = vanyaCount * 10 + (vanya[j++] - '0');
            }
            if (vanyaCount == 0) vanyaCount = 1;
        }

        long long take = min(pavelCount, vanyaCount);
        if (pavelChar != vanyaChar) diff += take;

        if (diff > k) return false;

        pavelCount -= take;
        vanyaCount -= take;
    }

    return diff <= k;
}

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    string rleCodePavel, rleCodeVanya;
    cin >> rleCodePavel >> rleCodeVanya;

    if (canBuy(rleCodePavel, rleCodeVanya, k)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}