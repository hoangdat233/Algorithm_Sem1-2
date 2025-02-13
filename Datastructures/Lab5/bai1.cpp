#include <iostream>
using namespace std;

struct Node {
    int k;
    int l;
    int r;
};

int *h;    
Node *t;   

int calcH(int v) {
    if (v == 0) return 0;  
    if (h[v] != -1) return h[v]; 
    int hl = calcH(t[v].l);  
    int hr = calcH(t[v].r);  
    return h[v] = 1 + max(hl, hr); 
}

int main() {
    int n;
    cin >> n;

    t = new Node[n + 1];
    h = new int[n + 1];
    for(int i = 0; i <= n; ++i) h[i] = -1;

    for (int i = 1; i <= n; ++i)
        cin >> t[i].k >> t[i].l >> t[i].r;

    for (int i = 1; i <= n; ++i) {
        int hl = calcH(t[i].l); 
        int hr = calcH(t[i].r); 
        cout << (hr - hl) << endl; 
    }
    delete[] t;
    delete[] h;

    return 0;
}
