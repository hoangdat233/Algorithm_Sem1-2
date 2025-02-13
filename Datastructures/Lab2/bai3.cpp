#include <iostream>

using namespace std;
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
void WorstCase(int n) {
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    for (int i = 2; i < n; ++i) {
        swap(arr,i,i/2);
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    WorstCase(n);
    return 0;
}