#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

struct Node {
    int key;
    int degree;
    bool marked;
    Node* parent;
    Node* child;
    Node* next;
    Node* prev;

    Node(int k) : key(k), degree(0), marked(false), parent(nullptr), child(nullptr), next(nullptr), prev(nullptr) {}
};

class FibonacciHeap {
private:
    Node* minNode;
    int numTrees;

    void link(Node* y, Node* x) {
        y->prev->next = y->next;
        y->next->prev = y->prev;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->next = y;
            y->prev = y;
        } else {
            y->next = x->child;
            y->prev = x->child->prev;
            x->child->prev->next = y;
            x->child->prev = y;
        }
        x->degree++;
        y->marked = false;
    }

    void consolidate() {
        vector<Node*> A(64, nullptr);
        Node* current = minNode;
        Node* end = minNode;

        if (current != nullptr) {
            do {
                Node* x = current;
                int d = x->degree;
                while (A[d] != nullptr) {
                    Node* y = A[d];
                    if (x->key > y->key) {
                        swap(x, y);
                    }
                    link(y, x);
                    A[d] = nullptr;
                    d++;
                }
                A[d] = x;
                current = current->next;
            } while (current != end);
        }

        minNode = nullptr;
        for (Node* node : A) {
            if (node != nullptr) {
                if (minNode == nullptr) {
                    minNode = node;
                    minNode->next = minNode;
                    minNode->prev = minNode;
                } else {
                    node->next = minNode;
                    node->prev = minNode->prev;
                    minNode->prev->next = node;
                    minNode->prev = node;
                    if (node->key < minNode->key) {
                        minNode = node;
                    }
                }
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), numTrees(0) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        if (minNode == nullptr) {
            minNode = newNode;
            minNode->next = minNode;
            minNode->prev = minNode;
        } else {
            newNode->next = minNode;
            newNode->prev = minNode->prev;
            minNode->prev->next = newNode;
            minNode->prev = newNode;
            if (key < minNode->key) {
                minNode = newNode;
            }
        }
        numTrees++;
    }

    int extractMin() {
        if (minNode == nullptr) return -1;

        Node* minNodeToExtract = minNode;
        int minKey = minNodeToExtract->key;

        if (minNodeToExtract->child != nullptr) {
            Node* child = minNodeToExtract->child;
            do {
                Node* nextChild = child->next;
                child->next = minNode;
                child->prev = minNode->prev;
                minNode->prev->next = child;
                minNode->prev = child;
                child->parent = nullptr;
                child = nextChild;
            } while (child != minNodeToExtract->child);
        }

        minNode->prev->next = minNode->next;
        minNode->next->prev = minNode->prev;

        if (minNode == minNode->next) {
            minNode = nullptr;
        } else {
            minNode = minNode->next;
            consolidate();
        }

        delete minNodeToExtract;
        numTrees--;
        return minKey;
    }

    void merge(FibonacciHeap& other) {
        if (other.minNode == nullptr) return;
        if (minNode == nullptr) {
            minNode = other.minNode;
        } else {
            Node* minNext = minNode->next;
            Node* otherMinNext = other.minNode->next;

            minNode->next = otherMinNext;
            otherMinNext->prev = minNode;
            other.minNode->next = minNext;
            minNext->prev = other.minNode;

            if (other.minNode->key < minNode->key) {
                minNode = other.minNode;
            }
        }
        numTrees += other.numTrees;
        other.minNode = nullptr;
        other.numTrees = 0;
    }

    Node* findNode(int key) {
        Node* current = minNode;
        if (current == nullptr) return nullptr;

        do {
            if (current->key == key) return current;
            Node* child = current->child;
            if (child != nullptr) {
                Node* found = findNodeInSubtree(child, key);
                if (found != nullptr) return found;
            }
            current = current->next;
        } while (current != minNode);

        return nullptr;
    }

    Node* findNodeInSubtree(Node* node, int key) {
        Node* current = node;
        do {
            if (current->key == key) return current;
            Node* child = current->child;
            if (child != nullptr) {
                Node* found = findNodeInSubtree(child, key);
                if (found != nullptr) return found;
            }
            current = current->next;
        } while (current != node);
        return nullptr;
    }

    void decreaseKey(int oldKey, int newKey) {
        Node* node = findNode(oldKey);
        if (node == nullptr || newKey > node->key) return;
        node->key = newKey;

        Node* parent = node->parent;
        if (parent != nullptr && node->key < parent->key) {
            if (node->next != node) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            if (parent->child == node) {
                parent->child = (node->next == node) ? nullptr : node->next;
            }
            parent->degree--;
            node->next = minNode;
            node->prev = minNode->prev;
            minNode->prev->next = node;
            minNode->prev = node;
            node->parent = nullptr;
            node->marked = false;
        }
        if (node->key < minNode->key) {
            minNode = node;
        }
    }

    Node* getMinNode() {
        return minNode;
    }
};

int main() {
    int n;
    cin >> n; // Number of operations
    vector<FibonacciHeap> heaps;
    string command;

    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "create") {
            heaps.emplace_back();
        } else if (command == "insert") {
            int k, x;
            cin >> k >> x;
            heaps[k].insert(x);
        } else if (command == "extract-min") {
            int k;
            cin >> k;
            int result = heaps[k].extractMin();
            if (result == -1) {
                cout << "*" << endl;
            } else {
                cout << result << endl;
            }
        } else if (command == "merge") {
            int k, m;
            cin >> k >> m;
            FibonacciHeap newHeap;
            newHeap.merge(heaps[k]);
            newHeap.merge(heaps[m]);
            heaps.push_back(newHeap);
        } else if (command == "decrease-key") {
            int k, x, y;
            cin >> k >> x >> y;
            heaps[k].decreaseKey(x, y);
        }
    }

    return 0;
}