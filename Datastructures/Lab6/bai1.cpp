#include <iostream>
using namespace std;

bool IsHeap(int a[], int n){
    for(int i = 1; i < n; i++){
        int left = 2*i ;
        int right = 2*i + 1;
        if (left <= n && a[i - 1] > a[left - 1]) return false;
        if (right <= n && a[i - 1] > a[right - 1]) return false;
    }
    return true;
}

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if (IsHeap(a, n)) cout << "YES";
    else cout << "NO";
    return 0;
}