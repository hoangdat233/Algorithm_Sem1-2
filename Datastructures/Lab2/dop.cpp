#include<iostream>
using namespace std;

void quicksort(int a[], int l, int r){
    int i = l, j = r;
    int mid = a[(l + r) / 2];
    while(i <= j){
        while(a[i] < mid){
            i++;
        }
        while(a[j] > mid){
            j--;
        }
        if(i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if(l < j) quicksort(a, l, j);
    if(i < r) quicksort(a, i, r);
}
int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i]=a[i]+i;
    }
    quicksort(a, 0, n - 1);
    for(int i = 0; i < n; i++){
        a[i]=a[i]-i;
    }
    bool check=true;
    for(int i = 1; i < n; i++){
        if(a[i-1]>a[i]){
            check=false;
            break;
        }
    }
    if(check){
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
    }
    else{
        cout << ":(";
    }
    return 0;
}