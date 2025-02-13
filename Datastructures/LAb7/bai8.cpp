#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> generateGrayCode(int n) {
    vector<string> grayCode;
    grayCode.push_back("0");
    grayCode.push_back("1");

    for (int i = 2; i <= n; ++i) {
        int size = grayCode.size();
        for (int j = size - 1; j >= 0; --j) {
            grayCode.push_back("1" + grayCode[j]);
            grayCode[j] = "0" + grayCode[j];
        }
    }

    return grayCode;
}

int main() {
    int n;
    cin >> n;

    vector<string> grayCode = generateGrayCode(n);
    for (const string &code : grayCode) {
        cout << code << endl;
    }

    return 0;
}
