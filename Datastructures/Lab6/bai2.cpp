#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct PriorityQueue {
    vector<int> heap;

    void siftUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[parent] <= heap[idx]) break;
            swap(heap[parent], heap[idx]);
            idx = parent;
        }
    }

    void siftDown(int idx) {
        int n = heap.size();
        while (idx * 2 + 1 < n) {
            int left = idx * 2 + 1;
            int right = idx * 2 + 2;
            int smallest = idx;
            if (left < n && heap[left] < heap[smallest]) smallest = left;
            if (right < n && heap[right] < heap[smallest]) smallest = right;
            if (smallest == idx) break;
            swap(heap[smallest], heap[idx]);
            idx = smallest;
        }
    }

    void insert(int x) {
        heap.push_back(x);
        siftUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) return -1; 
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0); 
        return minVal;
    }

    void decreaseKey(int x, int y) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] == x) {
                heap[i] = y;
                siftUp(i); 
                break;
            }
        }
    }

    void merge(PriorityQueue& other) {
        for (int x : other.heap) {
            insert(x);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<PriorityQueue> queues;
    string operation;

    while (cin >> operation) {
        if (operation == "create") {
            queues.push_back(PriorityQueue());
        } else if (operation == "insert") {
            int k, x;
            cin >> k >> x;
            queues[k].insert(x);
        } else if (operation == "extract-min") {
            int k;
            cin >> k;
            int result = queues[k].extractMin();
            if (result == -1) {
                cout << "*\n";
            } else {
                cout << result << "\n";
            }
        } else if (operation == "merge") {
            int k, m;
            cin >> k >> m;
            queues.push_back(PriorityQueue());
            queues.back().merge(queues[k]);
            queues.back().merge(queues[m]);
        } else if (operation == "decrease-key") {
            int k, x, y;
            cin >> k >> x >> y;
            queues[k].decreaseKey(x, y);
        }
    }

    return 0;
}
