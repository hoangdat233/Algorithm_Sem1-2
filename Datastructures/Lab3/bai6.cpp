#include <iostream>
using namespace std;

void quickSort(int arr[], int left, int right) {
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

bool canPlace(int dist, int cows, int stalls[], int n) {
    int count = 1, last = stalls[0];
    for (int i = 1; i < n; i++) {
        if (stalls[i] - last >= dist) {
            count++;
            last = stalls[i];
        }
    }
    return count >= cows;
}

int binarySearch(int left, int right, int cows, int stalls[], int n) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canPlace(mid, cows, stalls, n)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left - 1;
}

int main(){
    int n,k;
    cin >> n >> k;
    int stalls[n];
    for (int i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    quickSort(stalls, 0, n - 1);

    int left = 0, right = stalls[n - 1] - stalls[0];
    cout << binarySearch(left, right, k, stalls, n);
    return 0;
}