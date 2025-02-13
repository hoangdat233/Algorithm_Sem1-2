#include <iostream>
#include <cstdlib>
using namespace std;

int random_p(long long l, long long r) {
    return l + rand() % (r - l + 1);
}
void swap(long long a[], long long i, long long j) {
    long long temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
int patition(long long a[], long long l, long long r) {
    long long pivot = a[random_p(l, r)];
    long long i = l-1;
    long long j = r+1;
    while(true){
        do{
            i++;
        }while(a[i] < pivot);
        do{
            j--;
        }while(a[j] > pivot);
        if(i >= j) return j;
        swap(a, i, j);
    }
}
void quick_sort(long long a[], long long l, long long r) {
    if(l>=r) return;
    long long pi = patition(a, l, r);
    quick_sort(a, l, pi);
    quick_sort(a, pi+1, r);
}
int main(){
    long long n;
    cin >> n;
    long long a[n];
    for(long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    srand(time(0));
    quick_sort(a, 0, n-1);
    long long new_m[n];
    for(long long i = 0; i < n; i++) {
        new_m[i] = 0;
    }
    long long left = 0;
    long long right = n-1;
    while(right>0){
        if(a[right]==a[right-1]){
            new_m[left] = a[right];
            right-=2;
            left++;
        }
        else if(a[right]-1==a[right-1]){    
            new_m[left] = a[right]-1;
            right-=2;
            left++;
        }
        else{
            right--;
        }
    }
    long long sum = 0;
    for (long long i = 0; i < n; i+=2) {
        sum += new_m[i]*new_m[i+1];
    }
    cout << sum;
    return 0;
}    