#include <iostream>
#include <cstdlib>  
using namespace std;

int random_pivot(int l, int r) {
    return l + rand() % (r - l + 1); 
}

// QuickSort с использованием Hoare partition
int hoare_partition(int* arr, int left, int right) {
    int pivotValue = arr[left];  
    int i = left - 1;
    int j = right + 1;

    while (true) {

        do {
            i++;
        } while (arr[i] < pivotValue);

        do {
            j--;
        } while (arr[j] > pivotValue);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = hoare_partition(arr, left, right);
        quicksort(arr, left, pivot);
        quicksort(arr, pivot + 1, right);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    int A, B, C, a1, a2;
    cin >> A >> B >> C >> a1 >> a2;
    int* b = new int[n];
    int* e = new int[n];
    b[0] = e[0] = a1;
    b[1] = e[0] = a2;
    int cnt=0,p=2; 
    for (int i = 2; i < n; ++i) {
        int m = A * b[i - 2] + B * b[i - 1] + C;
        if (m >= 0) {
            e[p]=m;  
            p++;
        }
    }
    quicksort(e, 0, p - 1);
    int res = 0;
    for (int i = p - k; i < p ; ++i) {
        res = res ^ e[i];
    }
    cout << res << endl;
    delete[] e;

    return 0;
}











