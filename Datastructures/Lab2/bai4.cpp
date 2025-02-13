#include <iostream>
#include <cstdlib>
using namespace std;

int random_pivot(int l, int r) {
    return l + rand() % (r - l + 1); 
}

int partition(int a[], int l, int r){
    int p=a[random_pivot(l,r)];
    int i=l-1,j=r+1;
    while(true){
        do{
            i++;
        }while(a[i]<p);
        do{
            j--;
        }while(a[j]>p);
        if(i<j) std::swap(a[i],a[j]);
        else return j;
    }
}

void quickSort(int a[], int l, int r) {
    if(l>=r) return;
    int p=partition(a,l,r);
    quickSort(a,l,p);
    quickSort(a,p+1,r);
}
int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int n;
    cin >> n;
    int start[n], end[n];
    for(int i = 0; i < n; i++){
        cin >> start[i] >> end[i];
    }
    quickSort(start, 0, n-1);
    quickSort(end, 0, n-1);

    int cnt =0;
    int current_start = start[0], current_end = end[0];
    for(int i = 1; i < n; i++){
        if(start[i] <= current_end){
            current_end = max(current_end, end[i]);
        }
        else{
            cnt += current_end - current_start + 1;
            current_start = start[i];
            current_end = end[i];
        }
    }
    cnt += current_end - current_start + 1;
    cout << cnt;
    return 0;
}
