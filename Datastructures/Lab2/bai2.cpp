#include <iostream>
#include <cstdlib>
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

int main(){
    int n; std::cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) std::cin >> a[i];
    quickSort(a,0,n-1);
    for(int i = 0; i < n; i++) std::cout << a[i] << " ";
    return 0;
}

