#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    int height;
    Node* left;
    Node* right;

    Node(string k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, string key, bool& isDuplicate) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key, isDuplicate);
    else if (key > node->key)
        node->right = insert(node->right, key, isDuplicate);
    else {
        isDuplicate = true;
        return node;  
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

int countUniqueChars(const string& str) {
    bool char_seen[256] = {false};
    for (char c : str) {
        char_seen[c] = true;
    }
    int unique_count = 0;
    for (int i = 0; i < 256; ++i) {
        if (char_seen[i]) {
            ++unique_count;
        }
    }
    return unique_count;
}

int main() {
    int n;
    cin >> n;
    Node* root = nullptr;
    int memory_saved = 0;

    for (int i = 0; i < n; ++i) {
        string contact;
        cin >> contact;
        bool isDuplicate = false;
        root = insert(root, contact, isDuplicate);
        if (isDuplicate) {
            memory_saved += countUniqueChars(contact);
        }
    }

    cout << memory_saved << endl;
    return 0;
}
