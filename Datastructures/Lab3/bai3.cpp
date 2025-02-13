#include <iostream>
#include <vector>
#include <string>

using namespace std;

void CountingSort(vector<string> &a, int k, int pos ){
    int n = a.size();
    vector<int> count(256, 0);
    vector<string> b(n);

    for(int i = 0; i < n; i++){
        count[a[i][k-pos-1]]++;
    }

    for(int i = 1; i < 256; i++){
        count[i] += count[i-1];
    }

    for(int i = n-1; i >= 0; i--){
        b[count[a[i][k-pos-1]]-1] = a[i];
        count[a[i][k-pos-1]]--;
    }

    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
}

void RadixSort(vector<string> &a, int k, int t){
    for(int i = 0; i < t; i++){
        CountingSort(a, k, i);
    }
}

int main(){
    int n, k, t;
    cin >> n >> k >> t;
    vector<string> mes(n);
    for(int i = 0; i < n; i++){
        cin >> mes[i];
    }
    RadixSort(mes, k, t);
    for(int i = 0; i < n; i++){
        cout << mes[i] << "\n";
    }
    return 0;
}


