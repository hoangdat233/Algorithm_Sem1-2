#include <iostream>
using namespace std;

const int MAXN = 1000000;
int maxHeap[MAXN], maxSize = 0; 
int minHeap[MAXN], minSize = 0; 

void pushMaxHeap(int x) {
    maxHeap[maxSize++] = x;
    int i = maxSize - 1;
    while (i > 0 && maxHeap[i] > maxHeap[(i - 1) / 2]) {
        swap(maxHeap[i], maxHeap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int popMaxHeap() {
    int res = maxHeap[0];
    maxHeap[0] = maxHeap[--maxSize];
    int i = 0;
    while (2 * i + 1 < maxSize) {
        int j = 2 * i + 1;
        if (j + 1 < maxSize && maxHeap[j] < maxHeap[j + 1]) j++;
        if (maxHeap[i] >= maxHeap[j]) break;
        swap(maxHeap[i], maxHeap[j]);
        i = j;
    }
    return res;
}

void pushMinHeap(int x) {
    minHeap[minSize++] = x;
    int i = minSize - 1;
    while (i > 0 && minHeap[i] < minHeap[(i - 1) / 2]) {
        swap(minHeap[i], minHeap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int popMinHeap() {
    int res = minHeap[0];
    minHeap[0] = minHeap[--minSize];
    int i = 0;
    while (2 * i + 1 < minSize) {
        int j = 2 * i + 1;
        if (j + 1 < minSize && minHeap[j] > minHeap[j + 1]) j++;
        if (minHeap[i] <= minHeap[j]) break;
        swap(minHeap[i], minHeap[j]);
        i = j;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (maxSize == 0 || x <= maxHeap[0]) {
            pushMaxHeap(x);
        } else {
            pushMinHeap(x);
        }

        if (maxSize > minSize + 1) {
            pushMinHeap(popMaxHeap());
        } else if (minSize > maxSize) {
            pushMaxHeap(popMinHeap());
        }
        if (maxSize > minSize) {
            cout << maxHeap[0] << "\n";
        } else if (minSize > maxSize) {
            cout << minHeap[0] << "\n";
        } else {
            cout << (maxHeap[0] + minHeap[0]) / 2 << "\n";
        }
    }

    return 0;
}
