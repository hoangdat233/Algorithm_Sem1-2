#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool canPerformOperations(int a, int b) {
    // Kiểm tra các phép toán:
    // 1. A || B (OR): Luôn luôn true nếu ít nhất một trong a hoặc b khác 0
    bool orPossible = (a != 0 || b != 0);
    
    // 2. A -> B (Implication): True nếu A = 0 hoặc B ≠ 0
    bool implyPossible = (a == 0 || b != 0);
    
    // 3. A & B (AND): True nếu cả a và b khác 0
    bool andPossible = (a != 0 && b != 0);
    
    // 4. A ^ B (XOR): Luôn luôn true miễn là a và b là số nguyên hợp lệ
    bool xorPossible = true;
    
    // 5. !A (NOT): Luôn luôn true vì có thể phủ định a
    bool notPossible = true;
    
    // Kiểm tra tất cả các phép toán phải possible
    return orPossible && implyPossible && andPossible && xorPossible && notPossible;
}

int main() {
    int t;
    cin >> t; // Số test case
    
    while (t--) {
        string operation;
        cin >> operation;
        
        if (operation == "||") {
            int a, b;
            cin >> a >> b;
            if (canPerformOperations(a, b)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (operation == "->") {
            int a, b;
            cin >> a >> b;
            if (canPerformOperations(a, b)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (operation == "&") {
            int a, b;
            cin >> a >> b;
            if (canPerformOperations(a, b)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (operation == "^") {
            int a, b;
            cin >> a >> b;
            if (canPerformOperations(a, b)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (operation == "!") {
            int a;
            cin >> a;
            // Với !A, chỉ cần kiểm tra nếu a là số nguyên hợp lệ
            cout << "YES" << endl;
        }
    }
    
    return 0;
}